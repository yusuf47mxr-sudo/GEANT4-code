#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "PolarimeterSD.hh"
DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fLogicScatterer(nullptr),
  fLogicAbsorber(nullptr)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // --------------------------------------------------------
    // 1. Malzeme Tanımlamaları (NIST Veritabanından)
    // --------------------------------------------------------
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic"); // Vakum
    G4Material* scatter_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE"); // Düşük Z
    G4Material* absorber_mat = nist->FindOrBuildMaterial("G4_BGO"); // Yüksek Z

    // --------------------------------------------------------
    // 2. Dünya (World) Hacmi
    // --------------------------------------------------------
    G4double world_hx = 50.0*cm;
    G4double world_hy = 50.0*cm;
    G4double world_hz = 50.0*cm;

    G4Box* solidWorld = new G4Box("World", world_hx, world_hy, world_hz);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0,                  // Rotasyon yok
        G4ThreeVector(),    // Merkezde (0,0,0)
        logicWorld,         // Mantıksal hacmi
        "World",            // İsmi
        0,                  // Anne hacim (yok)
        false,              // Boolean operasyonu yok
        0,                  // Kopya numarası
        true);              // Çakışma kontrolü

    // --------------------------------------------------------
    // 3. Geometri Boyutları (Polarimetre Kolları)
    // --------------------------------------------------------
    
    // Saçıcı Silindir (Scatterer) - Z ekseni boyunca
    G4double scatter_rmin = 0.0*cm;
    G4double scatter_rmax = 1.0*cm;
    G4double scatter_hz   = 1.0*cm; // Yarı uzunluk (Toplam 2 cm)
    G4Tubs* solidScatterer = new G4Tubs("Scatterer", scatter_rmin, scatter_rmax, scatter_hz, 0.0*deg, 360.0*deg);
    fLogicScatterer = new G4LogicalVolume(solidScatterer, scatter_mat, "LogicScatterer");

    // Soğurucu Halka (Absorber) - Saçıcının etrafında
    G4double absorber_rmin = 3.0*cm;
    G4double absorber_rmax = 6.0*cm;
    G4double absorber_hz   = 2.0*cm; // Yarı uzunluk (Toplam 4 cm)
    G4Tubs* solidAbsorber = new G4Tubs("Absorber", absorber_rmin, absorber_rmax, absorber_hz, 0.0*deg, 360.0*deg);
    fLogicAbsorber = new G4LogicalVolume(solidAbsorber, absorber_mat, "LogicAbsorber");

    // --------------------------------------------------------
    // 4. Hacimlerin Yerleştirilmesi (+Z ve -Z Yönlerine)
    // --------------------------------------------------------
    G4double arm_distance = 15.0*cm; // Merkezden uzaklık

    // Kol 1 (+Z Yönü)
    new G4PVPlacement(0, G4ThreeVector(0, 0, arm_distance), fLogicScatterer, "Scatterer_Arm1", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, arm_distance), fLogicAbsorber, "Absorber_Arm1", logicWorld, false, 1, true);

    // Kol 2 (-Z Yönü)
    new G4PVPlacement(0, G4ThreeVector(0, 0, -arm_distance), fLogicScatterer, "Scatterer_Arm2", logicWorld, false, 2, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, -arm_distance), fLogicAbsorber, "Absorber_Arm2", logicWorld, false, 2, true);

    // --------------------------------------------------------
    // 5. Görselleştirme Ayarları (Visualization Attributes)
    // --------------------------------------------------------
    G4VisAttributes* visWorld = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    visWorld->SetVisibility(false); // Dünyayı şeffaf yap
    logicWorld->SetVisAttributes(visWorld);

    G4VisAttributes* visScatter = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.5)); // Yarı saydam Mavi
    visScatter->SetForceSolid(true);
    fLogicScatterer->SetVisAttributes(visScatter);

    G4VisAttributes* visAbsorber = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.5)); // Yarı saydam Kırmızı
    visAbsorber->SetForceSolid(true);
    fLogicAbsorber->SetVisAttributes(visAbsorber);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
// 1. Geant4'ün SD Yöneticisini (Manager) çağır
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

    // 2. Kendi dinleme cihazımızdan bir nesne (object) yarat
    PolarimeterSD* polarimeterSD = new PolarimeterSD("PolarimeterSD");

    // 3. Cihazı Geant4 sistemine kaydet
    sdManager->AddNewDetector(polarimeterSD);

    // 4. Mantıksal hacimleri bu dinleme cihazına bağla
    // Hem saçıcının hem de soğurucunun verisini aynı tabloya yazmak istediğimiz için
    // ikisine de aynı SD nesnesini bağlıyoruz.
    SetSensitiveDetector(fLogicScatterer, polarimeterSD);
    SetSensitiveDetector(fLogicAbsorber, polarimeterSD);
}
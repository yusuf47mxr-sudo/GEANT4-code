#include "DetectorConstruction.hh"

// Geant4 Kütüphaneleri
#include "G4RunManager.hh"
#include "G4NistManager.hh" 
#include "G4Box.hh"
#include "G4Tubs.hh"           // <--- YENİ: Silindir Kütüphanesi
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }
 
DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // -------------------------------------------------------------------------
    // ADIM A: Malzemeler
    // -------------------------------------------------------------------------
    G4NistManager* nist = G4NistManager::Instance();
    
    // Ortam: HAVA
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    
    // NaI(Tl) için gerekli elementleri NIST'ten çağırıyoruz
    G4Element* elNa = nist->FindOrBuildElement("Na");
    G4Element* elI  = nist->FindOrBuildElement("I");
    G4Element* elTl = nist->FindOrBuildElement("Tl");

    // Yeni Malzeme: NaI(Tl) - Yoğunluk yaklaşık 3.67 g/cm3, 3 elementten oluşuyor
    G4Material* detector_mat = new G4Material("NaITl", 3.67*g/cm3, 3);
    
    // Elementleri kütlece yüzdelerine göre (Toplamı %100 olacak şekilde) ekliyoruz
    detector_mat->AddElement(elNa, 15.3 * perCent);
    detector_mat->AddElement(elI,  84.6 * perCent);
    detector_mat->AddElement(elTl,  0.1 * perCent);
    // -------------------------------------------------------------------------
    // ADIM B: Dünya (World)
    // -------------------------------------------------------------------------
    G4double world_sizeXY = 0.5 * m;
    G4double world_sizeZ  = 0.5 * m;
    
    G4Box* solidWorld = new G4Box("World", world_sizeXY, world_sizeXY, world_sizeZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    
    G4VPhysicalVolume* physWorld = 
        new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // -------------------------------------------------------------------------
    // ADIM C: DEV KRİSTAL (5x5 inç NaI)
    // -------------------------------------------------------------------------
    
    // BOYUT AYARLARI (5 inç)
    // Yarıçap = 2.5 inç (Çap 5 inç olsun diye)
    // Yarı Boy = 2.5 inç (Toplam Boy 5 inç olsun diye)
    G4double r_min = 0.0 * cm; // İçi dolu (delik yok)
    G4double r_max = 2.5 * 2.54 * cm; // 6.35 cm yarıçap
    G4double z_half = 2.5 * 2.54 * cm; // 6.35 cm yarı yükseklik
    
    // 1. ŞEKİL (Solid) - Silindir
    G4Tubs* solidDetector = new G4Tubs("Kristal_Solid", 
                                       r_min,    // İç yarıçap
                                       r_max,    // Dış yarıçap
                                       z_half,   // Yükseklik (Yarım!)
                                       0.*deg,   // Başlangıç açısı
                                       360.*deg);// Bitiş açısı (Tam tur)
    
    // 2. MANTIK (Logic) - Malzeme atama
    G4LogicalVolume* logicDetector = 
        new G4LogicalVolume(solidDetector, detector_mat, "Kristal_Logic");
    
    // 3. YERLEŞTİRME (Physical)
    new G4PVPlacement(0,                       // Dönme yok
                      G4ThreeVector(0,0,0),    // Dünyanın tam ortasına
                      logicDetector,           // Kristali koyuyoruz
                      "Kristal_Phys",          // Fiziksel isim
                      logicWorld,              // Dünyanın içine
                      false,                   // Boolean yok
                      0,                       // Kopya No
                      true);                   // Çakışma kontrolü

    // -------------------------------------------------------------------------
    // ADIM D: Veri Toplama Ayarı (Scoring)
    // -------------------------------------------------------------------------
    // Geant4'e diyoruz ki: "Enerjiyi bu kristalin içinde ölç!"
    fScoringVolume = logicDetector;

    return physWorld;
}
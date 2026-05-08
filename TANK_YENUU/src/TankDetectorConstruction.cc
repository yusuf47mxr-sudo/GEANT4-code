#include "TankDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

TankDetectorConstruction::TankDetectorConstruction() {}
TankDetectorConstruction::~TankDetectorConstruction() {}

G4VPhysicalVolume* TankDetectorConstruction::Construct() {
    // Malzeme Yöneticisi
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* env_air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* water   = nist->FindOrBuildMaterial("G4_WATER");

    // --- ÇERENKOV İÇİN EN KRİTİK NOKTA: SUYUN KIRMA İNDİSİ ---
    // Eğer bunu yapmazsan su ışığı kırmaz, mavi fotonlar oluşmaz!
    G4double photonEnergy[] = {2.0*eV, 3.4*eV}; // Görünür ışık aralığı
    G4double waterRINDEX[] = {1.33, 1.33};      // Suyun kırma indisi
    
    G4MaterialPropertiesTable* mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", photonEnergy, waterRINDEX, 2);
    water->SetMaterialPropertiesTable(mptWater); // Özelliği suya ekle

    // 1. DÜNYA (WORLD) - GÖRÜNMEZ YAPIYOM
    G4Box* solidWorld = new G4Box("World", 1.5*m, 1.5*m, 1.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, env_air, "World");
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible()); // Dünya görünmez olsun ki kalabalık yapmasın
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // 2. SU TANKI - İÇİ DOLU SU
    // Yarıçap: 52.5 cm, Yarı-boy: 60 cm
    G4Tubs* solidTank = new G4Tubs("SuTanki", 0.*cm, 52.5*cm, 60.0*cm, 0.*deg, 360.*deg);
    G4LogicalVolume* logicTank = new G4LogicalVolume(solidTank, water, "SuTanki");
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicTank, "SuTanki", logicWorld, false, 0, true);

    // --- GÖRSELLİK: TANKI YEŞİL TEL ÖRGÜ YAP! ---
    G4VisAttributes* tankVis = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Yeşil renk
    tankVis->SetForceWireframe(true); // İçi boş kafes (tel örgü) gibi çiz
    logicTank->SetVisAttributes(tankVis);

    return physWorld;
}
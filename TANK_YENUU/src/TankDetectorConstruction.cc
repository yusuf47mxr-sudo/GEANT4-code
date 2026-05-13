#include "TankDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4OpticalSurface.hh"      
#include "G4LogicalSkinSurface.hh"  

TankDetectorConstruction::TankDetectorConstruction() {}
TankDetectorConstruction::~TankDetectorConstruction() {}

G4VPhysicalVolume* TankDetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Material* env_air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* water   = nist->FindOrBuildMaterial("G4_WATER");

    // SADECE SUYUN KIRMA İNDİSİ
    G4double photonEnergy[] = {1.5*eV, 3.4*eV};
    G4double waterRINDEX[]  = {1.33, 1.33}; 
    
    G4MaterialPropertiesTable* mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", photonEnergy, waterRINDEX, 2);
    water->SetMaterialPropertiesTable(mptWater);

    // DÜNYA VE TANK
    G4Box* solidWorld = new G4Box("World", 1.5*m, 1.5*m, 1.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, env_air, "World");
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible()); 
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    G4Tubs* solidTank = new G4Tubs("SuTanki", 0.*cm, 52.5*cm, 60.0*cm, 0.*deg, 360.*deg);
    G4LogicalVolume* logicTank = new G4LogicalVolume(solidTank, water, "SuTanki");
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicTank, "SuTanki", logicWorld, false, 0, true);

    G4VisAttributes* tankVis = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); 
    tankVis->SetForceWireframe(true); 
    logicTank->SetVisAttributes(tankVis);

    // =========================================================
    // SİYAH DUVAR: DUVARE ÇARPAN FOTONU ANINDA YUT (SEKMEYİ ÖNLER)
    // =========================================================
    G4OpticalSurface* zifiriKaranlik = new G4OpticalSurface("ZifiriKaranlik");
    zifiriKaranlik->SetType(dielectric_metal);
    zifiriKaranlik->SetFinish(polished);
    zifiriKaranlik->SetModel(unified);

    G4double yansimaSifir[] = {0.0, 0.0};  
    G4double yutmaYuzdeYuz[] = {1.0, 1.0}; 

    G4MaterialPropertiesTable* mptSiyah = new G4MaterialPropertiesTable();
    mptSiyah->AddProperty("REFLECTIVITY", photonEnergy, yansimaSifir, 2);
    mptSiyah->AddProperty("EFFICIENCY", photonEnergy, yutmaYuzdeYuz, 2);
    zifiriKaranlik->SetMaterialPropertiesTable(mptSiyah);

    new G4LogicalSkinSurface("TankSiyahKaplama", logicTank, zifiriKaranlik);
    // =========================================================

    return physWorld;
}
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
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* scatter_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
    G4Material* absorber_mat = nist->FindOrBuildMaterial("G4_BGO");

    G4double world_hx = 50.0*cm;
    G4double world_hy = 50.0*cm;
    G4double world_hz = 50.0*cm;

    G4Box* solidWorld = new G4Box("World", world_hx, world_hy, world_hz);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0,
        G4ThreeVector(),
        logicWorld,
        "World",
        0,
        false,
        0,
        true);

    
    G4double scatter_rmin = 0.0*cm;
    G4double scatter_rmax = 1.0*cm;
    G4double scatter_hz   = 1.0*cm;
    G4Tubs* solidScatterer = new G4Tubs("Scatterer", scatter_rmin, scatter_rmax, scatter_hz, 0.0*deg, 360.0*deg);
    fLogicScatterer = new G4LogicalVolume(solidScatterer, scatter_mat, "LogicScatterer");

    G4double absorber_rmin = 3.0*cm;
    G4double absorber_rmax = 6.0*cm;
    G4double absorber_hz   = 2.0*cm;
    G4Tubs* solidAbsorber = new G4Tubs("Absorber", absorber_rmin, absorber_rmax, absorber_hz, 0.0*deg, 360.0*deg);
    fLogicAbsorber = new G4LogicalVolume(solidAbsorber, absorber_mat, "LogicAbsorber");

    G4double arm_distance = 15.0*cm;

    new G4PVPlacement(0, G4ThreeVector(0, 0, arm_distance), fLogicScatterer, "Scatterer_Arm1", logicWorld, false, 1, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, arm_distance), fLogicAbsorber, "Absorber_Arm1", logicWorld, false, 1, true);

    new G4PVPlacement(0, G4ThreeVector(0, 0, -arm_distance), fLogicScatterer, "Scatterer_Arm2", logicWorld, false, 2, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0, -arm_distance), fLogicAbsorber, "Absorber_Arm2", logicWorld, false, 2, true);

    G4VisAttributes* visWorld = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    visWorld->SetVisibility(false);
    logicWorld->SetVisAttributes(visWorld);

    G4VisAttributes* visScatter = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.5));
    visScatter->SetForceSolid(true);
    fLogicScatterer->SetVisAttributes(visScatter);

    G4VisAttributes* visAbsorber = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.5));
    visAbsorber->SetForceSolid(true);
    fLogicAbsorber->SetVisAttributes(visAbsorber);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

    PolarimeterSD* polarimeterSD = new PolarimeterSD("PolarimeterSD");

    sdManager->AddNewDetector(polarimeterSD);

    SetSensitiveDetector(fLogicScatterer, polarimeterSD);
    SetSensitiveDetector(fLogicAbsorber, polarimeterSD);
}
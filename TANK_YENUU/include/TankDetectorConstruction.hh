#ifndef TankDetectorConstruction_h
#define TankDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

class TankDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    TankDetectorConstruction();
    virtual ~TankDetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
};

#endif
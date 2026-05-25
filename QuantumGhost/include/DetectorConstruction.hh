#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

private:
    // İleride Sensitive Detector (Duyarlı Dedektör) atamak için
    // mantıksal hacimleri sınıf üyesi olarak tanımlıyoruz.
    G4LogicalVolume* fLogicScatterer;
    G4LogicalVolume* fLogicAbsorber;
};

#endif
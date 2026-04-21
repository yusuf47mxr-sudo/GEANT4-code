#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // --- İŞTE EKSİK OLAN KISIM BURASIYDI ---
    // Diğer sınıfların (SteppingAction) dedektöre ulaşması için bu gereklidir.
    const G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    // Bu değişkeni tanımlamazsak bilgisayar "fScoringVolume nedir?" der.
    G4LogicalVolume* fScoringVolume;
};

#endif
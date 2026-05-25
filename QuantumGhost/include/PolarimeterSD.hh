#ifndef PolarimeterSD_h
#define PolarimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;

class PolarimeterSD : public G4VSensitiveDetector {
public:
    PolarimeterSD(G4String name);
    virtual ~PolarimeterSD();

    // Sistemin kalbi: Her etkileşim adımında çalışacak fonksiyon
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* history);
};

#endif
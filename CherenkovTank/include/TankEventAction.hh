#ifndef TANK_EVENT_ACTION_HH
#define TANK_EVENT_ACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

class TankEventAction : public G4UserEventAction {
public:
    TankEventAction() = default;
    ~TankEventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddPhoton() { fPhotons++; }

private:
    G4double fEdep = 0.0;
    G4int fPhotons = 0;
};

#endif
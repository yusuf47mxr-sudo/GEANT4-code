#ifndef TANK_RUN_ACTION_HH
#define TANK_RUN_ACTION_HH

#include "G4UserRunAction.hh"

class TankRunAction : public G4UserRunAction {
public:
    TankRunAction();
    ~TankRunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};

#endif
#ifndef TANK_STEPPING_ACTION_HH
#define TANK_STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"

class TankEventAction;

class TankSteppingAction : public G4UserSteppingAction {
public:
    TankSteppingAction(TankEventAction* eventAction);
    ~TankSteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;

private:
    TankEventAction* fEventAction;
};

#endif
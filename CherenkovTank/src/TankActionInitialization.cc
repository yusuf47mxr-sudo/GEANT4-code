#include "TankActionInitialization.hh"
#include "TankPrimaryGeneratorAction.hh"
#include "TankRunAction.hh"
#include "TankEventAction.hh"
#include "TankSteppingAction.hh"

TankActionInitialization::TankActionInitialization() : G4VUserActionInitialization() {}

TankActionInitialization::~TankActionInitialization() {}

void TankActionInitialization::BuildForMaster() const {
    SetUserAction(new TankRunAction());
}

void TankActionInitialization::Build() const {
    SetUserAction(new TankPrimaryGeneratorAction());
    
    TankRunAction* runAction = new TankRunAction();
    SetUserAction(runAction);
    
    TankEventAction* eventAction = new TankEventAction();
    SetUserAction(eventAction);
    
    SetUserAction(new TankSteppingAction(eventAction));
}
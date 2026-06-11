#include "TankActionInitialization.hh"
#include "TankPrimaryGeneratorAction.hh"
#include "TankRunAction.hh"
#include "TankEventAction.hh"
#include "TankSteppingAction.hh"

TankActionInitialization::TankActionInitialization() : G4VUserActionInitialization() {}

TankActionInitialization::~TankActionInitialization() {}

// Bu kısım sadece Ana Yönetici (Master Thread) için çalışır
void TankActionInitialization::BuildForMaster() const {
    SetUserAction(new TankRunAction());
}

// Bu kısım 12 işçi çekirdeğin (Worker Threads) her biri için ayrı ayrı çalışır
void TankActionInitialization::Build() const {
    SetUserAction(new TankPrimaryGeneratorAction());
    
    TankRunAction* runAction = new TankRunAction();
    SetUserAction(runAction);
    
    TankEventAction* eventAction = new TankEventAction();
    SetUserAction(eventAction);
    
    SetUserAction(new TankSteppingAction(eventAction));
}
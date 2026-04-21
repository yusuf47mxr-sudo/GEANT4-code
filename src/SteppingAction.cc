#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction) // Muhasebeciyi tanıdık
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // 1. Bu adımda ne kadar enerji bırakıldı? (dE/dx)
    G4double edep = step->GetTotalEnergyDeposit();

    // 2. Eğer enerji bırakılmadıysa uğraşma, dön.
    if (edep <= 0.) return;

    // 3. Enerjiyi Muhasebeciye (EventAction) teslim et.
    fEventAction->AddEdep(edep);
}
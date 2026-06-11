#include "TankSteppingAction.hh"
#include "TankEventAction.hh"
#include "G4Step.hh"
#include "G4OpticalPhoton.hh"

#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
TankSteppingAction::TankSteppingAction(TankEventAction* eventAction)
    : fEventAction(eventAction) {}


void TankSteppingAction::UserSteppingAction(const G4Step* step) {
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);

    G4ThreeVector parentDirection = step->GetPreStepPoint()->GetMomentumDirection();
    auto analysisManager = G4AnalysisManager::Instance();

    auto secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries) {
        for (auto track : *secondaries) {
            if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
                fEventAction->AddPhoton();

                if (track->GetCreatorProcess() && track->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
                    G4ThreeVector photonDirection = track->GetMomentumDirection();
                    G4double angleRad = parentDirection.angle(photonDirection);
                    G4double angleDeg = angleRad * 180.0 / CLHEP::pi;

                    analysisManager->FillNtupleDColumn(1, 0, angleDeg);
                    analysisManager->AddNtupleRow(1);
                }
            }
        }
    }
}
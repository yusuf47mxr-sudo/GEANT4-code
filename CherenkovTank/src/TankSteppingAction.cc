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
    // Sadece su tankı hacmi içindeki enerji birikimi ve fotonlar sayılır;
    // world hacmindeki (tanktan kaçan/absorbe olmayan) adımlar göz ardı edilir.
    const G4String& volumeName = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    if (volumeName != "SuTanki") return;

    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);

    G4ThreeVector parentDirection = step->GetPreStepPoint()->GetMomentumDirection();
    auto analysisManager = G4AnalysisManager::Instance();

    auto secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries) {
        for (auto track : *secondaries) {
            if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() &&
                track->GetCreatorProcess() &&
                track->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
                fEventAction->AddPhoton();

                G4ThreeVector photonDirection = track->GetMomentumDirection();
                G4double angleRad = parentDirection.angle(photonDirection);
                G4double angleDeg = angleRad * 180.0 / CLHEP::pi;

                analysisManager->FillNtupleDColumn(1, 0, angleDeg);
                analysisManager->AddNtupleRow(1);
            }
        }
    }
}
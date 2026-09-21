#include "TankEventAction.hh"
#include "G4AnalysisManager.hh"

void TankEventAction::BeginOfEventAction(const G4Event*) {
    fEdep = 0.0;
    fPhotons = 0;
}

void TankEventAction::EndOfEventAction(const G4Event*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, fEdep);
    analysisManager->FillNtupleIColumn(1, fPhotons);
    analysisManager->AddNtupleRow();
}
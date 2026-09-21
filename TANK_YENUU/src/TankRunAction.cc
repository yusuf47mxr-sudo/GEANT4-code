#include "TankRunAction.hh"
#include "G4AnalysisManager.hh"

TankRunAction::TankRunAction() {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");
    
    analysisManager->SetNtupleMerging(true);

    analysisManager->SetFileName("TANK_Cikti"); 

    analysisManager->CreateNtuple("TankData", "Simulasyon Verileri");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->CreateNtupleIColumn("Photons");
    analysisManager->FinishNtuple();

    analysisManager->CreateNtuple("PhotonData", "Cherenkov Foton Verileri");
    analysisManager->CreateNtupleDColumn("CherenkovAngle");
    analysisManager->FinishNtuple();
}

void TankRunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->OpenFile();
}

void TankRunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
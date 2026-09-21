#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction(): G4UserRunAction()
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->SetDefaultFileType("root");
    
    analysisManager->CreateNtuple("ComptonData", "Kuantum Dolaniklik Verileri");
    analysisManager->CreateNtupleIColumn("EventID");
    analysisManager->CreateNtupleIColumn("VolumeID");
    analysisManager->CreateNtupleDColumn("Energy_keV");
    analysisManager->CreateNtupleDColumn("PosX_mm");
    analysisManager->CreateNtupleDColumn("PosY_mm");
    analysisManager->CreateNtupleDColumn("PosZ_mm");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{ }

void RunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("QuantumPolarimeterData.root");
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
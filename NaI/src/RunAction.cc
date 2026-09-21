#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->OpenFile("Veri.root");

    analysisManager->CreateNtuple("Olaylar", "Dedektor Verisi");

    analysisManager->CreateNtupleDColumn("Enerji_MeV");

    analysisManager->FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();

    G4cout << "### Dosya Kaydedildi: Veri.root ###" << G4endl;
}
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction()
: G4UserRunAction()
{
    // Analiz Yöneticisini Başlat
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Sadece .root formatında kaydetmesini istiyoruz
    analysisManager->SetDefaultFileType("root");
    
    // Tablo (Ntuple) Mimarisini Kuruyoruz
    analysisManager->CreateNtuple("ComptonData", "Kuantum Dolaniklik Verileri");
    analysisManager->CreateNtupleIColumn("EventID"); // Sütun 0
    analysisManager->CreateNtupleIColumn("VolumeID"); // Sütun 1 (1:Saçıcı, 2:Soğurucu)
    analysisManager->CreateNtupleDColumn("Energy_keV"); // Sütun 2
    analysisManager->CreateNtupleDColumn("PosX_mm"); // Sütun 3
    analysisManager->CreateNtupleDColumn("PosY_mm"); // Sütun 4
    analysisManager->CreateNtupleDColumn("PosZ_mm"); // Sütun 5
    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{ }

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Simülasyon başladığında verilerin yazılacağı dosyayı oluştur ve aç
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("QuantumPolarimeterData.root");
}

void RunAction::EndOfRunAction(const G4Run*)
{
    // Simülasyon bittiğinde verileri diske yaz ve dosyayı güvenle kapat
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
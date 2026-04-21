#include "RunAction.hh"
#include "G4AnalysisManager.hh" // <--- Analiz Müdürü

RunAction::RunAction()
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Analiz Müdürünü Çağır
    auto analysisManager = G4AnalysisManager::Instance();

    // 1. Dosya Adını Koy (Uproot ile bunu okuyacaksın)
    analysisManager->OpenFile("Veri.root");

    // 2. Tabloyu (Ntuple) Oluştur
    // "Olaylar" tablonun adı, "Dedektor Verisi" açıklaması
    analysisManager->CreateNtuple("Olaylar", "Dedektor Verisi");

    // 3. Sütunları Aç (Şimdilik sadece Enerji)
    // ID: 0 olacak
    analysisManager->CreateNtupleDColumn("Enerji_MeV");

    // 4. Tablo kurulumunu bitir
    analysisManager->FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    // Verileri diske yaz ve dosyayı kapat
    analysisManager->Write();
    analysisManager->CloseFile();

    G4cout << "### Dosya Kaydedildi: Veri.root ###" << G4endl;
}
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh" // <--- Analiz Müdürü

EventAction::EventAction()
: G4UserEventAction(),
  fEdep(0.)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    // Enerji 0'dan büyükse işlem yap
    if (fEdep > 0.) {
        
        // --- RAM KORUMA SİSTEMİ ---
        // Her olayı değil, sadece 1000. olayları ekrana yaz
        if (event->GetEventID() % 1000 == 0) {
            G4cout << ">>> İlerliyor... Olay ID: " << event->GetEventID() 
                   << " | Enerji: " << G4BestUnit(fEdep, "Energy") 
                   << G4endl;
        }
        // -------------------------

        // Analiz verisini kaydet (Burası sessizce çalışmaya devam eder)
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(0, fEdep);
        analysisManager->AddNtupleRow();  
    } 
}


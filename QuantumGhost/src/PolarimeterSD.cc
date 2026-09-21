#include "PolarimeterSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

PolarimeterSD::PolarimeterSD(G4String name)
: G4VSensitiveDetector(name)
{ }

PolarimeterSD::~PolarimeterSD()
{ }

G4bool PolarimeterSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    if (edep == 0.) return false;

    G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();

    G4String volumeName = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

    G4int volID = 0;
    if (volumeName.contains("Scatterer")) volID = 1;
    else if (volumeName.contains("Absorber")) volID = 2;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->FillNtupleIColumn(0, eventID);
    analysisManager->FillNtupleIColumn(1, volID);
    analysisManager->FillNtupleDColumn(2, edep / keV);
    analysisManager->FillNtupleDColumn(3, position.x() / mm);
    analysisManager->FillNtupleDColumn(4, position.y() / mm);
    analysisManager->FillNtupleDColumn(5, position.z() / mm);
    
    analysisManager->AddNtupleRow();

    return true;
}







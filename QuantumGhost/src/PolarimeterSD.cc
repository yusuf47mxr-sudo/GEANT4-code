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
    // 1. Enerji Birikimini Al (Foton enerji bıraktı mı?)
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    // Eğer enerji bırakılmadıysa (örneğin sadece uçarak geçtiyse) yoksay
    if (edep == 0.) return false;

    // 2. Etkileşimin Noktasal Konumunu Al
    G4ThreeVector position = aStep->GetPostStepPoint()->GetPosition();

    // 3. Etkileşimin Hangi Hacimde Gerçekleştiğini Bul
    G4String volumeName = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

    // Hacmi sayısal bir koda çevirelim ki veriyi işlemek kolay olsun
    // Scatterer (Saçıcı) = 1, Absorber (Soğurucu) = 2
    G4int volID = 0;
    if (volumeName.contains("Scatterer")) volID = 1;
    else if (volumeName.contains("Absorber")) volID = 2;

    // 4. Hangi Olayda (Event) Olduğumuzu Bul (Python'da gruplama yapmak için kritik)
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    // 5. Verileri Dosyaya Yazmak Üzere Analysis Manager'a Gönder
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Sütun İndekslerimiz: 
    // 0: EventID, 1: HacimID, 2: Enerji(keV), 3: X(mm), 4: Y(mm), 5: Z(mm)
    analysisManager->FillNtupleIColumn(0, eventID);
    analysisManager->FillNtupleIColumn(1, volID);
    analysisManager->FillNtupleDColumn(2, edep / keV);
    analysisManager->FillNtupleDColumn(3, position.x() / mm);
    analysisManager->FillNtupleDColumn(4, position.y() / mm);
    analysisManager->FillNtupleDColumn(5, position.z() / mm);
    
    // Tabloya yeni bir satır olarak ekle
    analysisManager->AddNtupleRow();

    return true;
}







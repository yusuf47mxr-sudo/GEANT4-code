#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"  // <--- BU ÇOK ÖNEMLİ, YOKSA HATA VERİR!


class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    G4double fEdep;
};

#endif
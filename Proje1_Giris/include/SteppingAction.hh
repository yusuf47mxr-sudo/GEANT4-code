#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"


class EventAction; // Muhasebeciyi önceden haber veriyoruz

class SteppingAction : public G4UserSteppingAction
{
  public:
    // Kurucu fonksiyonda EventAction'ı alacağız
    SteppingAction(EventAction* eventAction);
    ~SteppingAction() override;

    // Her adımda çalışacak ana fonksiyon
    void UserSteppingAction(const G4Step* step) override;

  private:
    EventAction* fEventAction; // Muhasebecinin adresi
};

#endif
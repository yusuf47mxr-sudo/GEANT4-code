


#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"      // <--- YENİ EKLENDİ
#include "EventAction.hh"    // <--- YENİ EKLENDİ
#include "SteppingAction.hh" // <--- YENİ EKLENDİ

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
    // 1. Tabancayı Tanıt (Zaten vardı)
    SetUserAction(new PrimaryGeneratorAction());

    // 2. Deney Yöneticisini Tanıt (RunAction - Yeni)
    SetUserAction(new RunAction());

    // 3. Muhasebeciyi Tanıt (EventAction - Yeni)
    // Bunu bir isme atıyoruz çünkü az sonra ajana teslim edeceğiz.
    auto eventAction = new EventAction();
    SetUserAction(eventAction);

    // 4. Ajanı Tanıt (SteppingAction - Yeni)
    // Ajan, topladığı enerjiyi kime vereceğini bilmeli (eventAction'ı veriyoruz).
    SetUserAction(new SteppingAction(eventAction));
}
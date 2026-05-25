#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{ }

ActionInitialization::~ActionInitialization()
{ }

void ActionInitialization::BuildForMaster() const
{
    // Master çekirdek sadece genel akışı (Run) kontrol eder
    SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    // İşçi çekirdekler hem jeneratörü ateşler hem de veriyi kaydeder
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());
}
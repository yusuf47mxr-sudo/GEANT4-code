#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    ~ActionInitialization() override;

    // Ana fonksiyon: İşçileri (Action sınıflarını) RunManager'a teslim eder.
    void Build() const override;
};

#endif
#ifndef TankActionInitialization_h
#define TankActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class TankActionInitialization : public G4VUserActionInitialization {
  public:
    TankActionInitialization();
    virtual ~TankActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
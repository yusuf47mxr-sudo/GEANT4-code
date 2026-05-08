#ifndef TankPhysicsList_h
#define TankPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class TankPhysicsList : public G4VModularPhysicsList {
  public:
    TankPhysicsList();
    virtual ~TankPhysicsList();
};

#endif
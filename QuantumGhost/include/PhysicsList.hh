#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsList : public G4VModularPhysicsList {
public:
    PhysicsList();
    virtual ~PhysicsList();

    // Parçacıkların (foton, elektron vb.) yaratılması
    virtual void ConstructParticle();
    
    // Kuralların (Compton, Fotoelektrik vb.) atanması
    virtual void ConstructProcess();
};

#endif
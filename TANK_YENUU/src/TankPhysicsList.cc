#include "TankPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

TankPhysicsList::TankPhysicsList() : G4VModularPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());
    
    RegisterPhysics(new G4OpticalPhysics());
}

TankPhysicsList::~TankPhysicsList() {}
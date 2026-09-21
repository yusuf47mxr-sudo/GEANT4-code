#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"

PhysicsList::PhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());

    RegisterPhysics(new G4DecayPhysics());

}

PhysicsList::~PhysicsList()
{
}
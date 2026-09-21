#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"

PhysicsList::PhysicsList() 
: G4VModularPhysicsList()
{
    SetVerboseLevel(1);

    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4EmLivermorePolarizedPhysics());

    RegisterPhysics(new G4EmExtraPhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
    RegisterPhysics(new G4StoppingPhysics());
    RegisterPhysics(new G4IonPhysics());
}

PhysicsList::~PhysicsList()
{ }

void PhysicsList::ConstructParticle()
{
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
}
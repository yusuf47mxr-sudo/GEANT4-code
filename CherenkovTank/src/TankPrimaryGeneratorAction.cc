#include "TankPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

TankPrimaryGeneratorAction::TankPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);
    
    fParticleGun->SetParticleEnergy(2.0*GeV);
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
}

TankPrimaryGeneratorAction::~TankPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void TankPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, 70.0*cm));
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    fParticleGun->SetParticleDefinition(particle);
    
    fParticleGun->SetParticleEnergy(511.0 * keV);
    
    fParticleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4double alpha = G4UniformRand() * CLHEP::twopi;

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
    
    G4ThreeVector polarization1(std::cos(alpha), std::sin(alpha), 0.0);
    fParticleGun->SetParticlePolarization(polarization1);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, -1.0));
    
    G4ThreeVector polarization2(-std::sin(alpha), std::cos(alpha), 0.0);
    fParticleGun->SetParticlePolarization(polarization2);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
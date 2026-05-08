#include "TankPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

TankPrimaryGeneratorAction::TankPrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    
    // Mermimiz: Müon eksi (mu-)
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);
    
    // Çerenkov ışıması için kritik enerji: 2 GeV
    fParticleGun->SetParticleEnergy(2.0*GeV);
    
    // Ateş yönü: Z ekseninde aşağıya doğru (-1)
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
}

TankPrimaryGeneratorAction::~TankPrimaryGeneratorAction()
{
    delete fParticleGun;
}

void TankPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Silahın konumu: Tankın biraz üstü (Z = 70 cm)
    fParticleGun->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, 70.0*cm));
    
    // Ateşle
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh" // Rastgele sayı üretmek için şart!

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Varsayılan parçacık: Gama
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);

  // Varsayılan Yön ve Konum
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-10.*cm));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // --- MANUAL MOD: COBALT-60 ---
  // Kodun içine gömülü (Hardcoded) enerji seçimi
  
  // %50 ihtimalle 1.17 MeV, %50 ihtimalle 1.33 MeV
  if (G4UniformRand() < 0.5) {
      fParticleGun->SetParticleEnergy(1.1732 * MeV); 
  } 
  else {
      fParticleGun->SetParticleEnergy(1.3325 * MeV); 
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
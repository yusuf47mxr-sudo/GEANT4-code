#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "Randomize.hh" // G4UniformRand() için gerekli

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
    // Sadece 1 adet parçacık tabancası oluşturuyoruz.
    // Aynı tabancayı farklı ayarlarla iki kez ateşleyeceğiz.
    fParticleGun = new G4ParticleGun(1);
    
    // Parçacık türünü Gamma (Foton) olarak ayarlıyoruz.
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    fParticleGun->SetParticleDefinition(particle);
    
    // Enerjiyi yok olma (annihilation) enerjisine sabitliyoruz.
    fParticleGun->SetParticleEnergy(511.0 * keV);
    
    // Tabancanın başlangıç pozisyonu merkez (orijin)
    fParticleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // -------------------------------------------------------------
    // 1. Kuantum Zarının Atılması (Rastgele Polarizasyon Açısı)
    // -------------------------------------------------------------
    // G4UniformRand() 0 ile 1 arasında rastgele bir sayı üretir.
    // Bunu 2*pi ile çarparak 0-360 derece arası rastgele bir radyan açısı (alpha) elde ederiz.
    G4double alpha = G4UniformRand() * CLHEP::twopi;

    // -------------------------------------------------------------
    // 2. Foton 1'in Üretilmesi (+Z Yönü)
    // -------------------------------------------------------------
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
    
    // Polarizasyon vektörü epsilon_1 = (cos(alpha), sin(alpha), 0)
    G4ThreeVector polarization1(std::cos(alpha), std::sin(alpha), 0.0);
    fParticleGun->SetParticlePolarization(polarization1);
    
    // Birinci fotonu olaya (event) ekle
    fParticleGun->GeneratePrimaryVertex(anEvent);

    // -------------------------------------------------------------
    // 3. Foton 2'nin Üretilmesi (-Z Yönü ve Dolanık Durum)
    // -------------------------------------------------------------
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, -1.0));
    
    // Polarizasyon vektörü epsilon_2 = (-sin(alpha), cos(alpha), 0)
    // epsilon_1 ve epsilon_2'nin nokta çarpımı (dot product) sıfırdır, yani birbirlerine diktir.
    G4ThreeVector polarization2(-std::sin(alpha), std::cos(alpha), 0.0);
    fParticleGun->SetParticlePolarization(polarization2);
    
    // İkinci fotonu olaya (event) ekle
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
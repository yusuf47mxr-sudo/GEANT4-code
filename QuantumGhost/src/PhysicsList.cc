#include "PhysicsList.hh"

// Gerekli Fizik Modülleri
#include "G4DecayPhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh" // BİZİM İÇİN EN KRİTİK MODÜL
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"

PhysicsList::PhysicsList() 
: G4VModularPhysicsList()
{
    // Simülasyonun çıktı ekranını (terminali) çok fazla bilgiyle boğmamak için
    // detay seviyesini (verbose level) düşürüyoruz.
    SetVerboseLevel(1);

    // 1. Temel Bozunma Kuralları
    RegisterPhysics(new G4DecayPhysics());

    // 2. Kuantum Dolanıklık İçin Özel Polarize Elektromanyetik Fizik
    // Standart G4EmStandardPhysics YERİNE bunu kullanıyoruz!
    RegisterPhysics(new G4EmLivermorePolarizedPhysics());

    // 3. İsteğe Bağlı Ekstra Fizik Paketleri (Eksiksiz bir simülasyon için)
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
    // Kayıtlı olan tüm fizik modüllerindeki parçacıkları sisteme tanıt
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    // Kayıtlı olan tüm fizik modüllerindeki etkileşimleri (Compton vb.) sisteme tanıt
    G4VModularPhysicsList::ConstructProcess();
}
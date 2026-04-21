#include "PhysicsList.hh"

// Geant4'ün hazır paketlerini çağırıyoruz
#include "G4EmStandardPhysics.hh"      // Standart Elektromanyetik (Gamma, e-, e+)
#include "G4OpticalPhysics.hh"         // Optik Fotonlar (Sintilasyon, Çerenkov) -> İstersen ekleriz
#include "G4DecayPhysics.hh"           // Radyoaktif Bozunma

PhysicsList::PhysicsList()
{
    // --- 1. ELEKTROMANYETİK FİZİK ---
    // Bu paket; gama, elektron, pozitron, proton ve müonların
    // standart etkileşimlerini (saçılma, iyonizasyon vb.) içerir.
    RegisterPhysics(new G4EmStandardPhysics());

    // --- 2. BOZUNMA FİZİĞİ ---
    // Kararsız parçacıkların bozulması için gereklidir.
    RegisterPhysics(new G4DecayPhysics());

    // İstersen ileride buraya "Hadronik Fizik" veya "Optik Fizik" de ekleyebilirsin.
    // RegisterPhysics(new G4OpticalPhysics()); 
}

PhysicsList::~PhysicsList()
{
    // Yıkıcı fonksiyon (Boş kalabilir)
}
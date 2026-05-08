#include "TankPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

TankPhysicsList::TankPhysicsList() : G4VModularPhysicsList()
{
    // Müonun suda ilerleyebilmesi için Standart Elektromanyetik Fizik
    RegisterPhysics(new G4EmStandardPhysics());
    
    // Mavi Çerenkov fotonlarının oluşabilmesi için Optik Fizik
    RegisterPhysics(new G4OpticalPhysics());
}

TankPhysicsList::~TankPhysicsList() {}
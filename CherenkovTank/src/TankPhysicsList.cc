#include "TankPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4OpticalParameters.hh"

TankPhysicsList::TankPhysicsList() : G4VModularPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());

    RegisterPhysics(new G4OpticalPhysics());

    // Cerenkov surecini fizikselce dogru ve stabil calisacak sekilde ayarla:
    // adim basina en fazla 300 foton uretilsin, parcacigin beta'sindaki
    // degisim adim basina en fazla %1 olsun, boylece adimlar arasi foton
    // sayisi tutarli kalir.
    G4OpticalParameters* opticalParams = G4OpticalParameters::Instance();
    opticalParams->SetCerenkovMaxPhotonsPerStep(300);
    opticalParams->SetCerenkovMaxBetaChange(1.0);
    opticalParams->SetCerenkovTrackSecondariesFirst(true);
}

TankPhysicsList::~TankPhysicsList() {}
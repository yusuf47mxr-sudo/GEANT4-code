#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    // Bu fonksiyon her simülasyon olayında (event) otomatik çağrılır
    virtual void GeneratePrimaries(G4Event* anEvent);

private:
    G4ParticleGun* fParticleGun;
};

#endif
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    // Bu metot her olayda (event) çağrılır
    virtual void GeneratePrimaries(G4Event*);         

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun* fParticleGun;
    G4Box* fEnvelopeBox;
};

#endif
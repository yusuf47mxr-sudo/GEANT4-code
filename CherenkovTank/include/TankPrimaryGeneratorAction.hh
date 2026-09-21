#ifndef TankPrimaryGeneratorAction_h
#define TankPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

class TankPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    TankPrimaryGeneratorAction();
    virtual ~TankPrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
  
  private:
    G4ParticleGun* fParticleGun;
};

#endif
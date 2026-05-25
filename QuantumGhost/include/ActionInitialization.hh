#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    virtual ~ActionInitialization();

    // Çoklu çekirdek (Multithreading) kullanırsak Master thread için
    virtual void BuildForMaster() const;
    
    // Standart çalışma (Worker thread) için
    virtual void Build() const;
};

#endif
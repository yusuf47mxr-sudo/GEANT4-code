#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    // Simülasyon başlarken çalışır (Dosya açma ve tablo kurma)
    virtual void BeginOfRunAction(const G4Run*);
    
    // Simülasyon biterken çalışır (Dosyayı kaydetme ve kapatma)
    virtual void EndOfRunAction(const G4Run*);
};

#endif
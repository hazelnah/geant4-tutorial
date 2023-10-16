#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "run.hh"

extern const bool gDebug;

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction* runAction);
    virtual ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { this->edep += edep; }

private:
    MyRunAction* runAction;
    G4double edep;
};

#endif

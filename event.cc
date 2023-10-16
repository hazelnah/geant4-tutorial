#include "event.hh"

MyEventAction::MyEventAction(MyRunAction* runAction)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* event)
{
	if (gDebug) G4cout << "Event::BeginOfEventAction"<< G4endl;
}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
	if (gDebug) G4cout << "Event::EndOfEventAction"<< G4endl;

    G4int evtID = event->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    
    man->FillNtupleIColumn(2, 0, evtID);
    man->FillNtupleDColumn(2, 1, event->GetPrimaryVertex(0)->GetX0());
    man->FillNtupleDColumn(2, 2, event->GetPrimaryVertex(0)->GetY0());
    man->FillNtupleDColumn(2, 3, event->GetPrimaryVertex(0)->GetZ0());
    man->AddNtupleRow(2);
}

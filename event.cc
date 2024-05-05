#include "event.hh"
#include "RunData.hh"
#include "G4RunManager.hh"

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
    auto runData = static_cast<RunData*>
        (G4RunManager::GetRunManager()->GetNonConstCurrentRun());

    G4double dT = G4RandGauss::shoot(0.5, 2*10e-2);
    while (dT<=0) dT = G4RandGauss::shoot(0.5, 2*10e-2);
    G4double t0 = runData->GetEventTime() + dT;
    
    evTime = runData->CalcEventTime();
    evTime = t0;
    runData->SetEventTime(t0);

    G4int evtID = event->GetEventID();
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    
    man->FillNtupleIColumn(2, 0, evtID);
    man->FillNtupleDColumn(2, 1, event->GetPrimaryVertex(0)->GetX0());
    man->FillNtupleDColumn(2, 2, event->GetPrimaryVertex(0)->GetY0());
    man->FillNtupleDColumn(2, 3, event->GetPrimaryVertex(0)->GetZ0());
    man->FillNtupleDColumn(2, 4, evTime);
    man->FillNtupleDColumn(2, 5, dT);
    man->AddNtupleRow(2);
}

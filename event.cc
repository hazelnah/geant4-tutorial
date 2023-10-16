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
{if (gDebug) G4cout << "Event::EndOfEventAction"<< G4endl;}

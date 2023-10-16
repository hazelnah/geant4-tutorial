#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction)
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step*)
{
    G4cout << "Stepping user act start" << G4endl;
    const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    scoringVolume = detectorConstruction->GetScoringVolume();
    G4cout << "Stepping user act end" << G4endl;
}

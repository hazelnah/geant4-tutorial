#include "run.hh"

MyRunAction::MyRunAction()
{   
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Particles", "Particles");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleDColumn("fEkin");
    man->CreateNtupleDColumn("fCharge");
    man->CreateNtupleDColumn("fMass");
    man->CreateNtupleSColumn("fName");
    man->CreateNtupleDColumn("fHitX"); // position of the cell
    man->CreateNtupleDColumn("fHitY");
    man->CreateNtupleDColumn("fHitZ");
    man->FinishNtuple(0);
    
    man->CreateNtuple("Mother", "Mother");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(1);

}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    if (gDebug) G4cout << "Run start" << std::endl;
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    G4int runID = run->GetRunID();
    if (gDebug) G4cout << "Run start 1" << std::endl;
    
    std::stringstream strRunID;
    strRunID << runID;
    
    man->OpenFile("output"+strRunID.str()+".root");
    if (gDebug) G4cout << "Run start 2" << std::endl;
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->Write();
    man->CloseFile();
}

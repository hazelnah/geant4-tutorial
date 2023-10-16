#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    if (gDebug) G4cout << "MyPhysicsList init"<< G4endl;
    RegisterPhysics (new G4EmStandardPhysics());
//    RegisterPhysics (new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new BiasedRDPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}

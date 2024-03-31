#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);
<<<<<<< Updated upstream
=======

    MyEventAction *evtAction = new MyEventAction(runAction);
    SetUserAction(evtAction);
    if (gDebug) G4cout << "Action end" << std::endl;
>>>>>>> Stashed changes
}

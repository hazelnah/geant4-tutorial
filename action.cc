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
    if (gDebug) G4cout << "Action start" << std::endl;
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction *evtAction = new MyEventAction(runAction);
    SetUserAction(evtAction);
    if (gDebug) G4cout << "Action end" << std::endl;
}

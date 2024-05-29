#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    nCols = 100;
    nRows = 100;
    
    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    
    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");
    
    fMessenger->DeclareProperty("cherenkov", cherenkov, "Activate Chreenkov Detector");
    fMessenger->DeclareProperty("scintillator", scintillator, "Activate Scintillator");
    
    DefineMaterials();
    
    xWorld = 1.*m;
    yWorld = 1.*m;
    zWorld = 1.*m;
    
    cherenkov = true;
    scintillator = false;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
    
    C = nist->FindOrBuildElement("C");
    SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
    
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);
    
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    
    Aerogel->SetMaterialPropertiesTable(mptAerogel);
    
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    
    worldMat->SetMaterialPropertiesTable(mptWorld);
}

void MyDetectorConstruction::ConstructCherenkov()
{
    solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    
    // logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
    
    // physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    
    solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, 0.01*m);
    
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    G4RotationMatrix * rotM = new G4RotationMatrix();
    rotM->rotateY(90*deg);
    
    for(G4int i = 0; i < nRows; i++)
    {
        for(G4int j = 0; j < nCols; j++)
        {
            // physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/nRows, -0.5*m+(j+0.5)*m/nCols, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
            physDetector = new G4PVPlacement(0, G4ThreeVector(-1*xWorld+xWorld*(2*i+1)/nRows, -1*yWorld+yWorld*(2*j+1)/nCols, 0.99*m), 
                            logicDetector, "physDetector", logicWorld, false, j+i*nCols, false); // swithed off the overlaps checking
            /*physDetector2 = new G4PVPlacement(rotM, G4ThreeVector(1.01*m, -1*yWorld+yWorld*(2*j+1)/nCols, -1*zWorld+zWorld*(2*i+1)/nRows), 
                            logicDetector, "physDetector2", logicWorld, false, j+i*nCols, false); // swithed off the overlaps checking*/
            // rotM = physDetector2->GetRotation();
            // rotM->rotateX(90*deg);
        }
    }
}

void MyDetectorConstruction::ConstructScintillator()
{  
    solidScint = new G4Tubs("solidScint", 10.*cm, 20.*cm, 20.*cm, 0.*deg, 360.*deg);
    
    logicScint = new G4LogicalVolume(solidScint, Aerogel, "logicalScint");
    
    physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicScint, "physScint", logicWorld, false, 0, true);
    
    fScoringVolume = logicScint;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{       
    if (gDebug) G4cout << "Construction start" << std::endl;
    solidWorld = new G4Box("solidWorld", xWorld+1*m, yWorld+1*m, zWorld+1*m);
    
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    if(cherenkov)
    	ConstructCherenkov();
    	
    if(scintillator)
        ConstructScintillator();
    
    if (gDebug) G4cout << "Construction end" << std::endl;
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    
    if(cherenkov)
    	logicDetector->SetSensitiveDetector(sensDet);
    	
    if(scintillator)
    	logicScint->SetSensitiveDetector(sensDet);
}

/*G4VPhysicalVolume *MyDetectorConstruction::Construct()
{    
    G4double xWorld = 0.5*m;
    G4double yWorld = 0.5*m;
    G4double zWorld = 0.5*m;
    
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    
    logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
    
    physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
    
    solidDetector = new G4Box("solidDetector", xWorld/nRows, xWorld/nCols, 0.01*m);
    
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    
    for(G4int i = 0; i < nRows; i++)
    {
        for(G4int j = 0; j < nCols; j++)
        {
            physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/nRows, -0.5*m+(j+0.5)*m/nCols, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
        }
    }
    
    return physWorld;
}*/

#include "generator.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

#include "globals.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");
    
    G4ThreeVector pos(0.,0.,0.);
    G4ThreeVector mom(0.,0.,1.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(0.*GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    if (gDebug) G4cout << "Generate start" << std::endl;
    
    G4int Z = 92;
    G4int A = 236;
    G4double Q = 0.*eplus;
    G4double E = 6.255*MeV;

    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, E);
    fParticleGun->SetParticleDefinition(ion);    
    G4ThreeVector pos(0.,0.,0.);
    for (int i = 0; i < 1; ++i)
    {
        
        pos[0] = G4UniformRand()*0.48*m;
        pos[1] = G4UniformRand()*0.48*m;
        pos[2] = G4UniformRand()*0.48*m;
        fParticleGun->SetParticlePosition(pos);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

}

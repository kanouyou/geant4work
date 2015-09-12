#include "TargetPrimaryGeneratorAction.h"
#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

TargetPrimaryGeneratorAction::TargetPrimaryGeneratorAction() {
  fParticleGun = new G4GeneralParticleSource();
}

TargetPrimaryGeneratorAction::~TargetPrimaryGeneratorAction() {
  delete fParticleGun;
}

void TargetPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

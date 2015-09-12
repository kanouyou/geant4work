#ifndef TargetPrimaryGeneratorAction_HH
#define TargetPrimaryGeneratorAction_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class TargetPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    TargetPrimaryGeneratorAction();
	virtual ~TargetPrimaryGeneratorAction();
	virtual void GeneratePrimaries(G4Event*);

  private:
    G4GeneralParticleSource* fParticleGun;
};

#endif

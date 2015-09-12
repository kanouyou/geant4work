#ifndef TargetSteppingAction_HH
#define TargetSteppingAction_HH

#include "G4UserSteppingAction.hh"

class RunAction;
class DetectorConstruction;
class PrimaryGeneratorAction;

class TargetSteppingAction : public G4UserSteppingAction {
  public:
    TargetSteppingAction();
	~TargetSteppingAction();
	void UserSteppingAction(const G4Step*);
};

#endif

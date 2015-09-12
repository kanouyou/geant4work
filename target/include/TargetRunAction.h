#ifndef TargetRunAction_HH
#define TargetRunAction_HH

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class TargetRunAction : public G4UserRunAction {
  public:
    TargetRunAction();
	virtual ~TargetRunAction();
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction  (const G4Run*);
};

#endif

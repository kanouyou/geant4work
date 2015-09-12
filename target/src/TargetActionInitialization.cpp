#include "TargetActionInitialization.h"
#include "TargetPrimaryGeneratorAction.h"
#include "TargetRunAction.h"
#include "TargetEventAction.h"
#include "TargetSteppingAction.h"

TargetActionInitialization::TargetActionInitialization() : G4VUserActionInitialization() {}

TargetActionInitialization::~TargetActionInitialization() {}

void TargetActionInitialization::BuildForMaster() const {
  SetUserAction(new TargetRunAction);
}

void TargetActionInitialization::Build() const {
  SetUserAction(new TargetPrimaryGeneratorAction);
  SetUserAction(new TargetRunAction);
  SetUserAction(new TargetEventAction);
  SetUserAction(new TargetSteppingAction());
}

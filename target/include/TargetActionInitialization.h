#ifndef TargetActionInitialization_HH
#define TargetActionInitialization_HH

#include "G4VUserActionInitialization.hh"

class TargetActionInitialization : public G4VUserActionInitialization {
  public:
    TargetActionInitialization();
	virtual ~TargetActionInitialization();
	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif

#ifndef TargetEventAction_HH
#define TargetEventAction_HH

#include "G4UserEventAction.hh"
#include "TargetHits.h"
#include "globals.hh"

class TargetEventAction : public G4UserEventAction {
  public:
    TargetEventAction();
	virtual ~TargetEventAction();
	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction  (const G4Event* event);

  private:
    TargetHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
	G4int fHCID;
};

#endif

#ifndef TargetSD_HH
#define TargetSD_HH

#include <vector>
#include "G4VSensitiveDetector.hh"
#include "TargetHits.h"

class G4Step;
class G4HCofThisEvent;

class TargetSD : public G4VSensitiveDetector {
  public:
    TargetSD(const G4String& name, const G4String& hitsCollectionName);
	virtual ~TargetSD();
	// methods
	virtual void   Initialize (G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent (G4HCofThisEvent* hitCollection);

  private:
    TargetHitsCollection* fHitsCollection;
};

#endif

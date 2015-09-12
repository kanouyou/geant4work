#include "TargetSD.h"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

TargetSD::TargetSD(const G4String& name, const G4String& hitsCollectionName) : G4VSensitiveDetector(name) {
  collectionName.insert(hitsCollectionName);
}

TargetSD::~TargetSD() {}

void TargetSD::Initialize(G4HCofThisEvent* hce) {
  fHitsCollection = new TargetHitsCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool TargetSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
  G4StepPoint* preStep = step->GetPreStepPoint();
  G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());
  
  TargetHits* newHit = new TargetHits();
  newHit->SetTrackID   (step->GetTrack()->GetTrackID());
  newHit->SetPosition  (step->GetPreStepPoint()->GetPosition());
  newHit->SetEnergy    (step->GetPreStepPoint()->GetTotalEnergy());
  newHit->SetMomentum  (step->GetPreStepPoint()->GetMomentum());
  newHit->SetGlobalTime(step->GetPreStepPoint()->GetGlobalTime());
  newHit->SetParticle  (step->GetTrack()->GetDefinition());
  fHitsCollection->insert(newHit);

  return true;
}

void TargetSD::EndOfEvent(G4HCofThisEvent*) {
  if (verboseLevel>1) {
    G4cout << "\n ----> Hits collection: in this event they are " << fHitsCollection->entries() << G4endl;
	for (int i=0; i<fHitsCollection->entries(); i++)
	  (*fHitsCollection)[i]->Print();
  }
}

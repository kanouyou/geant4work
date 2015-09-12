#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "TargetHits.h"

//G4ThreadLocal 
G4Allocator<TargetHits>* TargetHitAllocator = 0;

TargetHits::TargetHits() : G4VHit() {
  fTrack    = -1;
  fPosition = G4ThreeVector();
  fEnergy   = 0.;
  fMomentum = G4ThreeVector();
  fTime     = 0.;
  fParticle = NULL;
}

TargetHits::TargetHits(const TargetHits& right) : G4VHit() {
  fTrack    = right.fTrack;
  fPosition = right.fPosition;
  fEnergy   = right.fEnergy;
  fMomentum = right.fMomentum;
  fTime     = right.fTime;
  fParticle = right.fParticle;
}

TargetHits::~TargetHits() {}

const TargetHits& TargetHits::operator=(const TargetHits& right) {
  fTrack    = right.fTrack;
  fPosition = right.fPosition;
  fEnergy   = right.fEnergy;
  fMomentum = right.fMomentum;
  fTime     = right.fTime;
  fParticle = right.fParticle;
  return *this;
}

G4int TargetHits::operator==(const TargetHits& right) const {
  return ( this==&right )?1:0;
}

void TargetHits::Draw() {
  G4VVisManager* pVisMan = G4VVisManager::GetConcreteInstance();
  if (pVisMan) {
    G4Circle circle(fPosition);
	circle.SetScreenSize(4.);
	circle.SetFillStyle(G4Circle::filled);
	G4Colour color(1., 0., 0.);
	G4VisAttributes attribs(color);
	circle.SetVisAttributes(attribs);
	pVisMan->Draw(circle);
  }
}

void TargetHits::Print() {
  G4cout << " ## trackID: " << fTrack << G4endl;
}

#ifndef TargetHits_HH
#define TargetHits_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "tls.hh"

class TargetHits : public G4VHit {
  public:
    TargetHits();
	TargetHits(const TargetHits&);
	virtual ~TargetHits();
	// operators
	const TargetHits& operator=(const TargetHits&);
	G4int operator==(const TargetHits&) const;
	inline void* operator new(size_t);
	inline void  operator delete(void*);
	// methods
	virtual void Draw ();
	virtual void Print();
	// set information
	inline void SetTrackID   (G4int track)            { fTrack    = track;    }
	inline void SetPosition  (G4ThreeVector position) { fPosition = position; }
	inline void SetEnergy    (G4double energy)        { fEnergy   = energy;   }
	inline void SetMomentum  (G4ThreeVector momentum) { fMomentum = momentum; }
	inline void SetGlobalTime(G4double time)          { fTime     = time;     }
    inline void SetParticle  (G4ParticleDefinition* pdg) { fParticle = pdg;   }
    // get information
	inline G4int                 GetTrackID   () { return fTrack;    }
	inline G4ThreeVector         GetPosition  () { return fPosition; }
	inline G4double              GetEnergy    () { return fEnergy;   }
	inline G4ThreeVector         GetMomentum  () { return fMomentum; }
	inline G4double              GetGlobalTime() { return fTime;     }
	inline G4ParticleDefinition* GetParticle  () { return fParticle; }

	private:
	  G4int         fTrack;
	  G4ThreeVector fPosition;
	  G4double      fEnergy;
	  G4ThreeVector fMomentum;
	  G4double      fTime;
	  G4ParticleDefinition* fParticle;
};

// /_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

typedef G4THitsCollection<TargetHits> TargetHitsCollection;

extern G4Allocator<TargetHits>* TargetHitAllocator;

inline void* TargetHits::operator new(size_t) {
  if (!TargetHitAllocator)
    TargetHitAllocator = new G4Allocator<TargetHits>;
  void *hit;
  hit = (void*) TargetHitAllocator->MallocSingle();
  return hit;
}

inline void TargetHits::operator delete(void *hit) {
  if (!TargetHitAllocator)
    TargetHitAllocator = new G4Allocator<TargetHits>;
  TargetHitAllocator->FreeSingle((TargetHits*) hit);
}

#endif

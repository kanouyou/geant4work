#include "TargetEventAction.h"
#include "TargetSD.h"
#include "TargetHits.h"
#include "TargetAnalysis.h"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

TargetEventAction::TargetEventAction() : G4UserEventAction() {
  fHCID = -1;
}

TargetEventAction::~TargetEventAction() {}

TargetHitsCollection* TargetEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const {
  TargetHitsCollection* hitsCollection = static_cast<TargetHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  if (!hitsCollection) 
    std::cout << "Cannot access hitsCollection ID " << hcID << std::endl;
  
  return hitsCollection;
}

void TargetEventAction::BeginOfEventAction(const G4Event*) {}

void TargetEventAction::EndOfEventAction(const G4Event* event) {
  if (fHCID==-1)
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("WorldHitsCollection");
  
  TargetHitsCollection* hc = GetHitsCollection(fHCID, event);
  TargetHits* hits = (*hc)[hc->entries()-1];
  
/*  G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  anaMan->FillNtupleIColumn(0, hits->GetTrackID());
  anaMan->FillNtupleDColumn(1, hits->GetPosition().x());
  anaMan->FillNtupleDColumn(2, hits->GetPosition().y());
  anaMan->FillNtupleDColumn(3, hits->GetPosition().z());
  anaMan->FillNtupleDColumn(4, hits->GetEnergy());
  anaMan->FillNtupleDColumn(5, hits->GetMomentum().x());
  anaMan->FillNtupleDColumn(6, hits->GetMomentum().y());
  anaMan->FillNtupleDColumn(7, hits->GetMomentum().z());
  anaMan->FillNtupleDColumn(8, hits->GetGlobalTime());
  anaMan->FillNtupleIColumn(9, hits->GetParticle()->GetPDGEncoding());
  anaMan->AddNtupleRow();*/
}


#include <cmath>
#include "TargetAnalysis.h"
#include "TargetSteppingAction.h"
#include "TargetDetectorConstruction.h"
#include "TargetPrimaryGeneratorAction.h"

#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"

TargetSteppingAction::TargetSteppingAction() {}

TargetSteppingAction::~TargetSteppingAction() {}

void TargetSteppingAction::UserSteppingAction(const G4Step* step) {
  G4String postVol;
  G4String preVol = step->GetPreStepPoint()->GetTouchable()->GetVolume()->GetLogicalVolume()->GetName(); 
  if (step->GetPostStepPoint()->GetTouchable()->GetVolume())
    postVol = step->GetPostStepPoint()->GetTouchable()->GetVolume()->GetLogicalVolume()->GetName();
  
  //std::cout << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << std::endl;

  if (preVol=="Target" && postVol=="World") {
    G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
    anaMan->FillNtupleIColumn(0, step->GetTrack()->GetTrackID());
    anaMan->FillNtupleDColumn(1, step->GetTrack()->GetPosition().x()/cm);
    anaMan->FillNtupleDColumn(2, step->GetTrack()->GetPosition().y()/cm);
    anaMan->FillNtupleDColumn(3, step->GetTrack()->GetPosition().z()/cm);
    anaMan->FillNtupleDColumn(4, step->GetTrack()->GetKineticEnergy()/MeV);
    anaMan->FillNtupleDColumn(5, step->GetTrack()->GetMomentum().x());
    anaMan->FillNtupleDColumn(6, step->GetTrack()->GetMomentum().y());
    anaMan->FillNtupleDColumn(7, step->GetTrack()->GetMomentum().z());
    anaMan->FillNtupleDColumn(8, step->GetTrack()->GetGlobalTime());
    anaMan->FillNtupleIColumn(9, step->GetTrack()->GetDefinition()->GetPDGEncoding());
    anaMan->AddNtupleRow();
  }
}


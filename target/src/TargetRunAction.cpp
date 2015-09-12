#include "TargetRunAction.h"
#include "TargetAnalysis.h"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

TargetRunAction::TargetRunAction() : G4UserRunAction() {
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  // create analysis manager
  G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  //G4cout << "Using " << anaMan->GetType() << G4endl;
  //anaMan->SetVerboseLevel(1);
  anaMan->SetFirstHistoId(1);
  // create ntuple
  anaMan->CreateNtuple("tree", "Data from GEANT4 Simulation");
  anaMan->CreateNtupleIColumn("track");
  anaMan->CreateNtupleDColumn("x");
  anaMan->CreateNtupleDColumn("y");
  anaMan->CreateNtupleDColumn("z");
  anaMan->CreateNtupleDColumn("energy");
  anaMan->CreateNtupleDColumn("px");
  anaMan->CreateNtupleDColumn("py");
  anaMan->CreateNtupleDColumn("pz");
  anaMan->CreateNtupleDColumn("time");
  anaMan->CreateNtupleIColumn("pdgcode");
  anaMan->FinishNtuple();
}

TargetRunAction::~TargetRunAction() {
  delete G4AnalysisManager::Instance();
}

void TargetRunAction::BeginOfRunAction(const G4Run*) {
  G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  anaMan->OpenFile("targetHits");
}

void TargetRunAction::EndOfRunAction(const G4Run*) {
  G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  anaMan->Write();
  anaMan->CloseFile();
}

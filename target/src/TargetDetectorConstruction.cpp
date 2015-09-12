#include "TargetDetectorConstruction.h"
#include "TargetSD.h"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

TargetDetectorConstruction::TargetDetectorConstruction() : G4VUserDetectorConstruction() {}

TargetDetectorConstruction::~TargetDetectorConstruction() {}

G4VPhysicalVolume* TargetDetectorConstruction::Construct() {
  G4NistManager* nist = G4NistManager::Instance();
  nist->SetVerbose(1);
  
  G4double rhoVacuum = CLHEP::universe_mean_density;
  G4double pVacuum   = 1.0e-19*pascal;
  G4double TVacuum   = 0.1*kelvin;
  G4Material* graphite = new G4Material("Graphite", 6., 12.*g/mole, 1.82*g/cm3);
  G4Material* vacuum   = new G4Material("Vacuum", 1., 1.01*g/mole, rhoVacuum, kStateGas, TVacuum, pVacuum);

  /****************************/
  // World
  /****************************/
  G4bool checkOverlaps = true;
  G4double earthRadius = 100*cm;
  G4Orb* worldSolid = new G4Orb("World", earthRadius);
  G4LogicalVolume*  logicWorld = new G4LogicalVolume(worldSolid, vacuum, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

  /****************************/
  // Target
  /****************************/
  G4VisAttributes* colorGraphite = new G4VisAttributes(G4Colour(0.8, 0.0, 0.0, 0.7));
  G4Tubs* targetSolid = new G4Tubs("Target", 0., 3*cm, 30.*cm, 0., 2*M_PI);
  G4LogicalVolume*  logicTarget = new G4LogicalVolume(targetSolid, graphite, "Target");
  G4VPhysicalVolume* physTarget = new G4PVPlacement(0, G4ThreeVector(), logicTarget, "Target", logicWorld, false, 0, checkOverlaps);
  logicTarget->SetVisAttributes(colorGraphite);
  
  return physWorld;
}

void TargetDetectorConstruction::ConstructSDandField() {
  TargetSD* sd = new TargetSD("WorldSD", "WorldHitsCollection");
  SetSensitiveDetector("World", sd);
}

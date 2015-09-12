#include "TargetDetectorConstruction.h"
#include "TargetActionInitialization.h"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "FTF_BIC.hh"
//#include "QGSP_INCLXX_HP.hh"
//#include "QGSP_BERT_HP.hh"
//#include "FTFP_BERT_HP.hh"
//#include "QGSP_BIC_HP.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc, char** argv) {
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

//#ifdef G4MULTITHREADED
#ifdef xxxG4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new TargetDetectorConstruction());

  G4VModularPhysicsList* physics = new FTF_BIC;
  //physics->SetVerboseLevel(1);
  runManager->SetUserInitialization(physics);

  runManager->SetUserInitialization(new TargetActionInitialization());
  runManager->Initialize();
  
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    G4String command  = "/control/execute ";
	G4String fileName = argv[1];
	UImanager->ApplyCommand(command+fileName);
  }
  else {
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
    UImanager->ApplyCommand("/control/execute init.mac");
#endif
    ui->SessionStart();
	delete ui;
#endif
  }

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

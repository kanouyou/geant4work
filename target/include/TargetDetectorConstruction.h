#ifndef TargetDetectorConstruction_HH
#define TargetDetectorConstruction_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class TargetDetectorConstruction : public G4VUserDetectorConstruction {
  public:
    TargetDetectorConstruction();
	virtual ~TargetDetectorConstruction();
	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

  private:
};

#endif

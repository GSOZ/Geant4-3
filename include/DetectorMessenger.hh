//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file optical/OpNovice2/include/DetectorMessenger.hh
/// \brief Definition of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger : public G4UImessenger
{
public:
	DetectorMessenger(DetectorConstruction*);
	~DetectorMessenger() override;

	void SetNewValue(G4UIcommand*, G4String) override;

private:
	DetectorConstruction* fDetector = nullptr;
	DetectorConstruction* fDetector2 = nullptr;
	DetectorConstruction* fDetector3 = nullptr;
	G4UIdirectory* fOpticalDir = nullptr;

	// the surface
	G4UIcmdWithAString* fSurfaceTypeCmd = nullptr;
	G4UIcmdWithAString* fSurfaceFinishCmd = nullptr;
	G4UIcmdWithAString* fSurfaceFinishCmd2 = nullptr;
	G4UIcmdWithAString* fSurfaceFinishCmd3 = nullptr;
	G4UIcmdWithAString* fSurfaceModelCmd = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd2 = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmdPET = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd3 = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd4 = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmdGr = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmdG = nullptr;
	G4UIcmdWithADouble* fSurfaceSigmaAlphaCmdR = nullptr;
	G4UIcmdWithADouble* fSurfacePolishCmd = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmd = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmd2 = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmdPET = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmd3 = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmd4 = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmdGr = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmdG = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropVectorCmdR = nullptr;
	G4UIcmdWithAString* fSurfaceMatPropConstCmd = nullptr;

	// the box
	G4UIcmdWithAString* fTankMatPropVectorCmd = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmd2 = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmdPET = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmd3 = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmd4 = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmdGr = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmdG = nullptr;
	G4UIcmdWithAString* fTankMatPropVectorCmdR = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmd = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmd2 = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmdPET = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmd3 = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmd4 = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmdGr = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmdG = nullptr;
	G4UIcmdWithAString* fTankMatPropConstCmdR = nullptr;
	G4UIcmdWithAString* fTankMaterialCmd = nullptr;
	G4UIcmdWithAString* fTankMaterialCmd2 = nullptr;
	G4UIcmdWithAString* fTankMaterialCmd3 = nullptr;

	// the world
	G4UIcmdWithAString* fWorldMatPropVectorCmd = nullptr;
	G4UIcmdWithAString* fWorldMatPropConstCmd = nullptr;
	G4UIcmdWithAString* fWorldMaterialCmd = nullptr;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

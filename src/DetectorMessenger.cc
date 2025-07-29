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
/// \file optical/OpNovice2/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"

#include "G4OpticalSurface.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"

#include <sstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
	: G4UImessenger()
	, fDetector(Det)
{
	fOpticalDir = new G4UIdirectory("/opnovice2/");
	fOpticalDir->SetGuidance("Parameters for optical simulation.");

	fSurfaceTypeCmd = new G4UIcmdWithAString("/opnovice2/surfaceType", this);
	fSurfaceTypeCmd->SetGuidance("Surface type.");
	fSurfaceTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceTypeCmd->SetToBeBroadcasted(false);

	fSurfaceFinishCmd = new G4UIcmdWithAString("/opnovice2/surfaceFinish", this);
	fSurfaceFinishCmd->SetGuidance("Surface finish.");
	fSurfaceFinishCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceFinishCmd->SetToBeBroadcasted(false);

	fSurfaceFinishCmd2 = new G4UIcmdWithAString("/opnovice2/surfaceFinish2", this);
	fSurfaceFinishCmd2->SetGuidance("Surface finish.");
	fSurfaceFinishCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceFinishCmd2->SetToBeBroadcasted(false);

	fSurfaceFinishCmd3 = new G4UIcmdWithAString("/opnovice2/surfaceFinish3", this);
	fSurfaceFinishCmd3->SetGuidance("Surface finish.");
	fSurfaceFinishCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceFinishCmd3->SetToBeBroadcasted(false);

	fSurfaceModelCmd = new G4UIcmdWithAString("/opnovice2/surfaceModel", this);
	fSurfaceModelCmd->SetGuidance("surface model.");
	fSurfaceModelCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceModelCmd->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmd =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlpha", this);
	fSurfaceSigmaAlphaCmd->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmd->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmd->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmd2 =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlpha2", this);
	fSurfaceSigmaAlphaCmd2->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmd2->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmd2->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmdPET =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlphaPET", this);
	fSurfaceSigmaAlphaCmdPET->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmdPET->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmdPET->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmdPET->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmd3 =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlpha3", this);
	fSurfaceSigmaAlphaCmd3->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmd3->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmd3->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmd4 =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlpha4", this);
	fSurfaceSigmaAlphaCmd4->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmd4->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmd4->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmd4->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmdGr =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlphaGr", this);
	fSurfaceSigmaAlphaCmdGr->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmdGr->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmdGr->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmdGr->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmdG =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlphaG", this);
	fSurfaceSigmaAlphaCmdG->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmdG->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmdG->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmdG->SetToBeBroadcasted(false);

	fSurfaceSigmaAlphaCmdR =
		new G4UIcmdWithADouble("/opnovice2/surfaceSigmaAlphaR", this);
	fSurfaceSigmaAlphaCmdR->SetGuidance("surface sigma alpha");
	fSurfaceSigmaAlphaCmdR->SetGuidance(" parameter.");
	fSurfaceSigmaAlphaCmdR->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceSigmaAlphaCmdR->SetToBeBroadcasted(false);

	fSurfacePolishCmd = new G4UIcmdWithADouble("/opnovice2/surfacePolish", this);
	fSurfacePolishCmd->SetGuidance("surface polish");
	fSurfacePolishCmd->SetGuidance(" parameter (for Glisur model).");
	fSurfacePolishCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfacePolishCmd->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmd =
		new G4UIcmdWithAString("/opnovice2/surfaceProperty", this);
	fSurfaceMatPropVectorCmd->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmd->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmd->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmd2 =
		new G4UIcmdWithAString("/opnovice2/surfaceProperty2", this);
	fSurfaceMatPropVectorCmd2->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmd2->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmd2->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmdPET =
		new G4UIcmdWithAString("/opnovice2/surfacePropertyPET", this);
	fSurfaceMatPropVectorCmdPET->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmdPET->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmdPET->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmdPET->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmd3 =
		new G4UIcmdWithAString("/opnovice2/surfaceProperty3", this);
	fSurfaceMatPropVectorCmd3->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmd3->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmd3->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmd4 =
		new G4UIcmdWithAString("/opnovice2/surfaceProperty4", this);
	fSurfaceMatPropVectorCmd4->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmd4->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmd4->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmd4->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmdGr =
		new G4UIcmdWithAString("/opnovice2/surfacePropertyGr", this);
	fSurfaceMatPropVectorCmdGr->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmdGr->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmdGr->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmdGr->SetToBeBroadcasted(false);


	fSurfaceMatPropVectorCmdG =
		new G4UIcmdWithAString("/opnovice2/surfacePropertyG", this);
	fSurfaceMatPropVectorCmdG->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmdG->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmdG->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmdG->SetToBeBroadcasted(false);

	fSurfaceMatPropVectorCmdR =
		new G4UIcmdWithAString("/opnovice2/surfacePropertyR", this);
	fSurfaceMatPropVectorCmdR->SetGuidance("Set material property vector");
	fSurfaceMatPropVectorCmdR->SetGuidance(" for the surface.");
	fSurfaceMatPropVectorCmdR->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropVectorCmdR->SetToBeBroadcasted(false);

	fSurfaceMatPropConstCmd =
		new G4UIcmdWithAString("/opnovice2/surfaceConstProperty", this);
	fSurfaceMatPropConstCmd->SetGuidance("Set material constant property");
	fSurfaceMatPropConstCmd->SetGuidance(" for the surface.");
	fSurfaceMatPropConstCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fSurfaceMatPropConstCmd->SetToBeBroadcasted(false);

	fTankMatPropVectorCmd =
		new G4UIcmdWithAString("/opnovice2/boxProperty", this);
	fTankMatPropVectorCmd->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmd->SetGuidance("the box.");
	fTankMatPropVectorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmd->SetToBeBroadcasted(false);

	fTankMatPropVectorCmd2 =
		new G4UIcmdWithAString("/opnovice2/boxProperty2", this);
	fTankMatPropVectorCmd2->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmd2->SetGuidance("the box.");
	fTankMatPropVectorCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmd2->SetToBeBroadcasted(false);

	fTankMatPropVectorCmdPET =
		new G4UIcmdWithAString("/opnovice2/boxPropertyPET", this);
	fTankMatPropVectorCmdPET->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmdPET->SetGuidance("the box.");
	fTankMatPropVectorCmdPET->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmdPET->SetToBeBroadcasted(false);

	fTankMatPropVectorCmd3 =
		new G4UIcmdWithAString("/opnovice2/boxProperty3", this);
	fTankMatPropVectorCmd3->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmd3->SetGuidance("the box.");
	fTankMatPropVectorCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmd3->SetToBeBroadcasted(false);

	fTankMatPropVectorCmd4 =
		new G4UIcmdWithAString("/opnovice2/boxProperty4", this);
	fTankMatPropVectorCmd4->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmd4->SetGuidance("the box.");
	fTankMatPropVectorCmd4->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmd4->SetToBeBroadcasted(false);

	fTankMatPropVectorCmdGr =
		new G4UIcmdWithAString("/opnovice2/boxPropertyGr", this);
	fTankMatPropVectorCmdGr->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmdGr->SetGuidance("the box.");
	fTankMatPropVectorCmdGr->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmdGr->SetToBeBroadcasted(false);


	fTankMatPropVectorCmdG =
		new G4UIcmdWithAString("/opnovice2/boxPropertyG", this);
	fTankMatPropVectorCmdG->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmdG->SetGuidance("the box.");
	fTankMatPropVectorCmdG->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmdG->SetToBeBroadcasted(false);

	fTankMatPropVectorCmdR =
		new G4UIcmdWithAString("/opnovice2/boxPropertyR", this);
	fTankMatPropVectorCmdR->SetGuidance("Set material property vector for ");
	fTankMatPropVectorCmdR->SetGuidance("the box.");
	fTankMatPropVectorCmdR->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropVectorCmdR->SetToBeBroadcasted(false);

	fTankMatPropConstCmd =
		new G4UIcmdWithAString("/opnovice2/boxConstProperty", this);
	fTankMatPropConstCmd->SetGuidance("Set material constant property ");
	fTankMatPropConstCmd->SetGuidance("for the box.");
	fTankMatPropConstCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmd->SetToBeBroadcasted(false);

	fTankMatPropConstCmd2 =
		new G4UIcmdWithAString("/opnovice2/boxConstProperty2", this);
	fTankMatPropConstCmd2->SetGuidance("Set material constant property ");
	fTankMatPropConstCmd2->SetGuidance("for the box.");
	fTankMatPropConstCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmd2->SetToBeBroadcasted(false);

	fTankMatPropConstCmdPET =
		new G4UIcmdWithAString("/opnovice2/boxConstPropertyPET", this);
	fTankMatPropConstCmdPET->SetGuidance("Set material constant property ");
	fTankMatPropConstCmdPET->SetGuidance("for the box.");
	fTankMatPropConstCmdPET->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmdPET->SetToBeBroadcasted(false);

	fTankMatPropConstCmd3 =
		new G4UIcmdWithAString("/opnovice2/boxConstProperty3", this);
	fTankMatPropConstCmd3->SetGuidance("Set material constant property ");
	fTankMatPropConstCmd3->SetGuidance("for the box.");
	fTankMatPropConstCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmd3->SetToBeBroadcasted(false);

	fTankMatPropConstCmd4 =
		new G4UIcmdWithAString("/opnovice2/boxConstProperty4", this);
	fTankMatPropConstCmd4->SetGuidance("Set material constant property ");
	fTankMatPropConstCmd4->SetGuidance("for the box.");
	fTankMatPropConstCmd4->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmd4->SetToBeBroadcasted(false);

	fTankMatPropConstCmdGr =
		new G4UIcmdWithAString("/opnovice2/boxConstPropertyGr", this);
	fTankMatPropConstCmdGr->SetGuidance("Set material constant property ");
	fTankMatPropConstCmdGr->SetGuidance("for the box.");
	fTankMatPropConstCmdGr->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmdGr->SetToBeBroadcasted(false);

	fTankMatPropConstCmdG =
		new G4UIcmdWithAString("/opnovice2/boxConstPropertyG", this);
	fTankMatPropConstCmdG->SetGuidance("Set material constant property ");
	fTankMatPropConstCmdG->SetGuidance("for the box.");
	fTankMatPropConstCmdG->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmdG->SetToBeBroadcasted(false);

	fTankMatPropConstCmdR =
		new G4UIcmdWithAString("/opnovice2/boxConstPropertyR", this);
	fTankMatPropConstCmdR->SetGuidance("Set material constant property ");
	fTankMatPropConstCmdR->SetGuidance("for the box.");
	fTankMatPropConstCmdR->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMatPropConstCmdR->SetToBeBroadcasted(false);

	fTankMaterialCmd = new G4UIcmdWithAString("/opnovice2/boxMaterial", this);
	fTankMaterialCmd->SetGuidance("Set material of box.");
	fTankMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMaterialCmd->SetToBeBroadcasted(false);

	fTankMaterialCmd2 = new G4UIcmdWithAString("/opnovice2/boxMaterial2", this);
	fTankMaterialCmd2->SetGuidance("Set material of box.");
	fTankMaterialCmd2->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMaterialCmd2->SetToBeBroadcasted(false);

	fTankMaterialCmd3 = new G4UIcmdWithAString("/opnovice2/boxMaterial3", this);
	fTankMaterialCmd3->SetGuidance("Set material of box.");
	fTankMaterialCmd3->AvailableForStates(G4State_PreInit, G4State_Idle);
	fTankMaterialCmd3->SetToBeBroadcasted(false);

	fWorldMatPropVectorCmd =
		new G4UIcmdWithAString("/opnovice2/worldProperty", this);
	fWorldMatPropVectorCmd->SetGuidance("Set material property vector ");
	fWorldMatPropVectorCmd->SetGuidance("for the world.");
	fWorldMatPropVectorCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fWorldMatPropVectorCmd->SetToBeBroadcasted(false);

	fWorldMatPropConstCmd =
		new G4UIcmdWithAString("/opnovice2/worldConstProperty", this);
	fWorldMatPropConstCmd->SetGuidance("Set material constant property");
	fWorldMatPropConstCmd->SetGuidance(" for the world.");
	fWorldMatPropConstCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fWorldMatPropConstCmd->SetToBeBroadcasted(false);

	fWorldMaterialCmd = new G4UIcmdWithAString("/opnovice2/worldMaterial", this);
	fWorldMaterialCmd->SetGuidance("Set material of world.");
	fWorldMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	fWorldMaterialCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
	delete fOpticalDir;
	delete fSurfaceFinishCmd;
	delete fSurfaceTypeCmd;
	delete fSurfaceModelCmd;
	delete fSurfaceSigmaAlphaCmd;
	delete fSurfaceSigmaAlphaCmd2;
	delete fSurfaceSigmaAlphaCmdPET;
	delete fSurfaceSigmaAlphaCmd3;
	delete fSurfaceSigmaAlphaCmd4;
	delete fSurfaceSigmaAlphaCmdGr;
	delete fSurfaceSigmaAlphaCmdG;
	delete fSurfaceSigmaAlphaCmdR;
	delete fSurfacePolishCmd;
	delete fSurfaceMatPropVectorCmd;
	delete fSurfaceMatPropVectorCmd2;
	delete fSurfaceMatPropVectorCmdPET;
	delete fSurfaceMatPropVectorCmd3;
	delete fSurfaceMatPropVectorCmd4;
	delete fSurfaceMatPropVectorCmdGr;
	delete fSurfaceMatPropVectorCmdG;
	delete fSurfaceMatPropVectorCmdR;
	delete fSurfaceMatPropConstCmd;
	delete fTankMatPropVectorCmd;
	delete fTankMatPropVectorCmd2;
	delete fTankMatPropVectorCmdPET;
	delete fTankMatPropVectorCmd3;
	delete fTankMatPropVectorCmd4;
	delete fTankMatPropVectorCmdGr;
	delete fTankMatPropVectorCmdG;
	delete fTankMatPropVectorCmdR;
	delete fTankMatPropConstCmd;
	delete fTankMatPropConstCmd2;
	delete fTankMatPropConstCmdPET;
	delete fTankMatPropConstCmd3;
	delete fTankMatPropConstCmd4;
	delete fTankMatPropConstCmdG;
	delete fTankMatPropConstCmdR;
	delete fTankMaterialCmd;
	delete fWorldMatPropVectorCmd;
	delete fWorldMatPropConstCmd;
	delete fWorldMaterialCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	//    FINISH
	if (command == fSurfaceFinishCmd)
	{
		if (newValue == "polished")
		{
			fDetector->SetSurfaceFinish(polished);
		}
		else if (newValue == "polishedfrontpainted")
		{
			fDetector->SetSurfaceFinish(polishedfrontpainted);
		}
		else if (newValue == "polishedbackpainted")
		{
			fDetector->SetSurfaceFinish(polishedbackpainted);
		}
		else if (newValue == "ground")
		{
			fDetector->SetSurfaceFinish(ground);
		}
		else if (newValue == "groundfrontpainted")
		{
			fDetector->SetSurfaceFinish(groundfrontpainted);
		}
		else if (newValue == "groundbackpainted")
		{
			fDetector->SetSurfaceFinish(groundbackpainted);
		}
		else if (newValue == "polishedlumirrorair")
		{
			fDetector->SetSurfaceFinish(polishedlumirrorair);
		}
		else if (newValue == "polishedlumirrorglue")
		{
			fDetector->SetSurfaceFinish(polishedlumirrorglue);
		}
		else if (newValue == "polishedair")
		{
			fDetector->SetSurfaceFinish(polishedair);
		}
		else if (newValue == "polishedteflonair")
		{
			fDetector->SetSurfaceFinish(polishedteflonair);
		}
		else if (newValue == "polishedtioair")
		{
			fDetector->SetSurfaceFinish(polishedtioair);
		}
		else if (newValue == "polishedtyvekair")
		{
			fDetector->SetSurfaceFinish(polishedtyvekair);
		}
		else if (newValue == "polishedvm2000air")
		{
			fDetector->SetSurfaceFinish(polishedvm2000air);
		}
		else if (newValue == "polishedvm2000glue")
		{
			fDetector->SetSurfaceFinish(polishedvm2000glue);
		}
		else if (newValue == "etchedlumirrorair")
		{
			fDetector->SetSurfaceFinish(etchedlumirrorair);
		}
		else if (newValue == "etchedlumirrorglue")
		{
			fDetector->SetSurfaceFinish(etchedlumirrorglue);
		}
		else if (newValue == "etchedair")
		{
			fDetector->SetSurfaceFinish(etchedair);
		}
		else if (newValue == "etchedteflonair")
		{
			fDetector->SetSurfaceFinish(etchedteflonair);
		}
		else if (newValue == "etchedtioair")
		{
			fDetector->SetSurfaceFinish(etchedtioair);
		}
		else if (newValue == "etchedtyvekair")
		{
			fDetector->SetSurfaceFinish(etchedtyvekair);
		}
		else if (newValue == "etchedvm2000air")
		{
			fDetector->SetSurfaceFinish(etchedvm2000air);
		}
		else if (newValue == "etchedvm2000glue")
		{
			fDetector->SetSurfaceFinish(etchedvm2000glue);
		}
		else if (newValue == "groundlumirrorair")
		{
			fDetector->SetSurfaceFinish(groundlumirrorair);
		}
		else if (newValue == "groundlumirrorglue")
		{
			fDetector->SetSurfaceFinish(groundlumirrorglue);
		}
		else if (newValue == "groundair")
		{
			fDetector->SetSurfaceFinish(groundair);
		}
		else if (newValue == "groundteflonair")
		{
			fDetector->SetSurfaceFinish(groundteflonair);
		}
		else if (newValue == "groundtioair")
		{
			fDetector->SetSurfaceFinish(groundtioair);
		}
		else if (newValue == "groundtyvekair")
		{
			fDetector->SetSurfaceFinish(groundtyvekair);
		}
		else if (newValue == "groundvm2000air")
		{
			fDetector->SetSurfaceFinish(groundvm2000air);
		}
		else if (newValue == "groundvm2000glue")
		{
			fDetector->SetSurfaceFinish(groundvm2000glue);
		}
		//         for Davis model
		else if (newValue == "Rough_LUT")
		{
			fDetector->SetSurfaceFinish(Rough_LUT);
		}
		else if (newValue == "RoughTeflon_LUT")
		{
			fDetector->SetSurfaceFinish(RoughTeflon_LUT);
		}
		else if (newValue == "RoughESR_LUT")
		{
			fDetector->SetSurfaceFinish(RoughESR_LUT);
		}
		else if (newValue == "RoughESRGrease_LUT")
		{
			fDetector->SetSurfaceFinish(RoughESRGrease_LUT);
		}
		else if (newValue == "Polished_LUT")
		{
			fDetector->SetSurfaceFinish(Polished_LUT);
		}
		else if (newValue == "PolishedTeflon_LUT")
		{
			fDetector->SetSurfaceFinish(PolishedTeflon_LUT);
		}
		else if (newValue == "PolishedESR_LUT")
		{
			fDetector->SetSurfaceFinish(PolishedESR_LUT);
		}
		else if (newValue == "PolishedESRGrease_LUT")
		{
			fDetector->SetSurfaceFinish(PolishedESRGrease_LUT);
		}
		else if (newValue == "Detector_LUT")
		{
			fDetector->SetSurfaceFinish(Detector_LUT);
		}
		else
		{
			G4ExceptionDescription ed;
			ed << "Invalid surface finish: " << newValue;
			G4Exception("DetectorMessenger", "OpNovice2_003", FatalException, ed);
		}
	}

	if (command == fSurfaceFinishCmd2)
	{
		if (newValue == "ground")
		{
			fDetector->SetSurfaceFinish2(ground);
		}
		else
		{
			G4ExceptionDescription ed;
			ed << "Invalid surface finish: " << newValue;
			G4Exception("DetectorMessenger", "OpNovice2_003", FatalException, ed);
		}
	}

	if (command == fSurfaceFinishCmd3)
	{
		if (newValue == "ground")
		{
			fDetector->SetSurfaceFinish3(ground);
		}
		else
		{
			G4ExceptionDescription ed;
			ed << "Invalid surface finish: " << newValue;
			G4Exception("DetectorMessenger", "OpNovice2_003", FatalException, ed);
		}
	}










	//  MODEL
	else if (command == fSurfaceModelCmd)
	{
		if (newValue == "glisur")
		{
			fDetector->SetSurfaceModel(glisur);
		}
		else if (newValue == "unified")
		{
			fDetector->SetSurfaceModel(unified);
		}
		else if (newValue == "LUT")
		{
			fDetector->SetSurfaceModel(LUT);
		}
		else if (newValue == "DAVIS")
		{
			fDetector->SetSurfaceModel(DAVIS);
		}
		else if (newValue == "dichroic")
		{
			fDetector->SetSurfaceModel(dichroic);
		}
		else
		{
			G4ExceptionDescription ed;
			ed << "Invalid surface model: " << newValue;
			G4Exception("DetectorMessenger", "ONovice2_001", FatalException, ed);
		}
	}

	// TYPE
	else if (command == fSurfaceTypeCmd)
	{
		if (newValue == "dielectric_metal")
		{
			fDetector->SetSurfaceType(dielectric_metal);
		}
		else if (newValue == "dielectric_dielectric")
		{
			fDetector->SetSurfaceType(dielectric_dielectric);
		}
		else if (newValue == "dielectric_LUT")
		{
			fDetector->SetSurfaceType(dielectric_LUT);
		}
		else if (newValue == "dielectric_LUTDAVIS")
		{
			fDetector->SetSurfaceType(dielectric_LUTDAVIS);
		}
		else if (newValue == "coated")
		{
			fDetector->SetSurfaceType(coated);
		}
		else
		{
			G4ExceptionDescription ed;
			ed << "Invalid surface type: " << newValue;
			G4Exception("DetectorMessenger", "OpNovice2_002", FatalException, ed);
		}
	}
	else if (command == fSurfaceSigmaAlphaCmd)
	{
		fDetector->SetSurfaceSigmaAlpha(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmd2)
	{
		fDetector->SetSurfaceSigmaAlpha2(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmdPET)
	{
		fDetector->SetSurfaceSigmaAlphaPET(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmd3)
	{
		fDetector->SetSurfaceSigmaAlpha3(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmd4)
	{
		fDetector->SetSurfaceSigmaAlpha4(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmdGr)
	{
		fDetector->SetSurfaceSigmaAlphaGr(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmdG)
	{
		fDetector->SetSurfaceSigmaAlphaG(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}
	else if (command == fSurfaceSigmaAlphaCmdR)
	{
		fDetector->SetSurfaceSigmaAlphaR(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}


	else if (command == fSurfacePolishCmd)
	{
		fDetector->SetSurfacePolish(
			G4UIcmdWithADouble::GetNewDoubleValue(newValue));
	}



	else if (command == fTankMatPropVectorCmd)    ///opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPV(prop, mpv);
	}



	else if (command == fTankMatPropVectorCmd2)    ///opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPV2(prop, mpv);
	}

	else if (command == fTankMatPropVectorCmdPET)    ///opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPVPET(prop, mpv);
	}

	else if (command == fTankMatPropVectorCmd3)    //opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPV3(prop, mpv);
	}

	else if (command == fTankMatPropVectorCmd4)    //opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPV4(prop, mpv);
	}

	else if (command == fTankMatPropVectorCmdGr)    //opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPVGr(prop, mpv);
	}


	else if (command == fTankMatPropVectorCmdG)    //opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddTankMPVG(prop, mpv);
	}

	else if (command == fTankMatPropVectorCmdR)    //opnovice2/boxProperty
	{
		// got a string. need to convert it to physics vector.
		// string format is property name, then pairs of energy, value
		// specify units for each value, eg 3.0*eV
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}

		fDetector->AddReflectorMPV(prop, mpv);
	}





	else if (command == fWorldMatPropVectorCmd)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		auto mpv = new G4MaterialPropertyVector();
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddWorldMPV(prop, mpv);
	}
	else if (command == fSurfaceMatPropVectorCmd)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPV(prop, mpv);
	}
	else if (command == fSurfaceMatPropVectorCmd2)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPV2(prop, mpv);
	}
	else if (command == fSurfaceMatPropVectorCmdPET)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPVPET(prop, mpv);
	}
	else if (command == fSurfaceMatPropVectorCmd3)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPV3(prop, mpv);
	}

	else if (command == fSurfaceMatPropVectorCmd4)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPV4(prop, mpv);
	}

	else if (command == fSurfaceMatPropVectorCmdGr)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPVGr(prop, mpv);
	}

	else if (command == fSurfaceMatPropVectorCmdG)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPVG(prop, mpv);
	}

	else if (command == fSurfaceMatPropVectorCmdR)
	{
		// Convert string to physics vector
		// string format is property name, then pairs of energy, value
		// space delimited
		auto mpv = new G4MaterialPropertyVector();
		G4cout << newValue << G4endl;
		std::istringstream instring(newValue);
		G4String prop;
		instring >> prop;
		while (instring)
		{
			G4String tmp;
			instring >> tmp;
			if (tmp == "")
			{
				break;
			}
			G4double en = G4UIcommand::ConvertToDouble(tmp);
			instring >> tmp;
			G4double val = G4UIcommand::ConvertToDouble(tmp);
			mpv->InsertValues(en, val);
		}
		fDetector->AddSurfaceMPVR(prop, mpv);
	}
	else if (command == fTankMatPropConstCmd)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPC(prop, val);
	}
	else if (command == fTankMatPropConstCmd2)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPC2(prop, val);
	}
	else if (command == fTankMatPropConstCmdPET)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPCPET(prop, val);
	}
	else if (command == fTankMatPropConstCmd3)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPC3(prop, val);
	}
	else if (command == fTankMatPropConstCmd4)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPC4(prop, val);
	}
	else if (command == fTankMatPropConstCmdGr)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPCGr(prop, val);
	}
	else if (command == fTankMatPropConstCmdG)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddTankMPCG(prop, val);
	}


	else if (command == fTankMatPropConstCmdR)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddReflectorMPC(prop, val);
	}
















	else if (command == fWorldMatPropConstCmd)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddWorldMPC(prop, val);
	}
	else if (command == fSurfaceMatPropConstCmd)
	{
		// Convert string to physics vector
		// string format is property name, then value
		// space delimited
		std::istringstream instring(newValue);
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble(tmp);
		fDetector->AddSurfaceMPC(prop, val);
	}
	else if (command == fWorldMaterialCmd)
	{
		fDetector->SetWorldMaterial(newValue);
	}


	else if (command == fTankMaterialCmd)
	{
		fDetector->SetTankMaterial(newValue);
	}
	else if (command == fTankMaterialCmd2)
	{
		fDetector2->SetTankMaterial2(newValue);
	}
	else if (command == fTankMaterialCmd3)
	{
		fDetector3->SetTankMaterial3(newValue);
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

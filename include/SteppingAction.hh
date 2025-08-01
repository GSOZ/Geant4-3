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
//
/// \file optical/OpNovice2/include/SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "DetectorConstruction.hh"

class DetectorConstruction;
class SteppingMessenger;

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(DetectorConstruction* detector);
	~SteppingAction() override;

	// method from the base class
	void UserSteppingAction(const G4Step*) override;

	inline G4int GetGammaCount() const { return gammaCount; }
	void ResetGammaCount() { gammaCount = 0; }

	inline void SetKillOnSecondSurface(G4bool val) { fKillOnSecondSurface = val; }
	inline G4bool GetKillOnSecondSurface() { return fKillOnSecondSurface; }

private:
	SteppingMessenger* fSteppingMessenger = nullptr;

	G4int gammaCount = 0;  //γ線カウント変数
	G4int fVerbose = 0;
	size_t fIdxVelocity = 0;

	G4bool fKillOnSecondSurface = false;
	DetectorConstruction* fDetector = nullptr;  // 追加: `fDetector` をメンバー変数として宣言
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

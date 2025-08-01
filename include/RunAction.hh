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
/// \file /optical/OpNovice2/include/RunAction.hh
/// \brief Definition of the RunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "SteppingAction.hh"  // γ線カウントのために追加
#include "G4String.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Run;
class HistoManager;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
public:
	// マスター用コンストラクタ
	RunAction(const G4String& outputFileName);

	// ワーカー用コンストラクタ
	RunAction(PrimaryGeneratorAction* primary, SteppingAction* stepping, const G4String& outputFileName);
	~RunAction() override;

	G4Run* GenerateRun() override;
	void BeginOfRunAction(const G4Run*) override;
	void EndOfRunAction(const G4Run*) override;

private:
	Run* fRun = nullptr;
	HistoManager* fHistoManager = nullptr;
	PrimaryGeneratorAction* fPrimary = nullptr;
	SteppingAction* fSteppingAction = nullptr;  // γカウント_SteppingAction を追加
	G4String fOutputFileName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*RunAction_h*/

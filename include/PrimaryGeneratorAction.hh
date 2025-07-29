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
/// \file optical/OpNovice2/include/PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"


class G4Event;
class PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction() override;

	void GeneratePrimaries(G4Event*) override;
	void SetSourceType(G4bool isAlpha);

	G4ParticleGun* GetParticleGun() { return fParticleGun; };

	void SetOptPhotonPolar();
	void SetOptPhotonPolar(G4double);
	void SetRandomDirection(G4bool val = true);
	G4bool GetPolarized() { return fPolarized; };
	G4double GetPolarization() { return fPolarization; }

	// originShiftのX成分を設定するための従来のsetter/getter（インスタンスごと）
	void SetOriginShiftY(G4double y) { fOriginShiftY = y; }
	G4double GetOriginShiftY() const { return fOriginShiftY; }

	// 全ワーカーで共有する原点シフト値を設定・取得する
	static void SetGlobalOriginShiftY(G4double y) { fGlobalOriginShiftY = y; }
	static G4double GetGlobalOriginShiftY() { return fGlobalOriginShiftY; }

private:
	G4ParticleGun* fParticleGun = nullptr;
	G4bool fIsAlphaSource; // α or β を切り替えるフラグ
	PrimaryGeneratorMessenger* fGunMessenger = nullptr;
	G4bool fRandomDirection = false;
	G4bool fPolarized = false;
	G4double fPolarization = 0.;
	G4double fOriginShiftY = 0.0;    // インスタンスごとの originShiftX（単位はmm）。初期値は0.0 mmとする。
	static G4double fGlobalOriginShiftY;	  // 全ワーカー共通の原点シフトX（mm単位）、初期値は0.0
};

#endif /*PrimaryGeneratorAction_h*/

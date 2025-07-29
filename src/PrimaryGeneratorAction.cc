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
/// \file optical/OpNovice2/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "G4Event.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGunMessenger.hh" 
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"
#include "G4ProcessManager.hh"


///////////////////////////////////////////////////////////////////////////////////////////
// 照射モード切替（DetectorConstruction.cc側も切り替えること）
//#define SELECT_ALPHA
//#define SELECT_BETA
#define SELECT_GAMMA
///////////////////////////////////////////////////////////////////////////////////////////
// 照射位置のランダム
//#define RANDAM

// 静的メンバ変数の定義：初期値 0.0 とする
G4double PrimaryGeneratorAction::fGlobalOriginShiftY = 0.0;

//////////////////////////////////////////////////////////////////////////////////////////
// PrimaryGeneratorAction コンストラクタ
//////////////////////////////////////////////////////////////////////////////////////////
PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr)
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4double particleEnergy = 0.0;


	// 起点（中心位置）の指定
#ifdef RANDAM
	G4double randomX = (G4UniformRand() * 10.0 - 5.0) * mm;
	G4double randomY = (G4UniformRand() * 10.0 - 5.0) * mm;
	G4ThreeVector originShift(randomX, randomY, 0.0 * mm);
	G4ThreeVector position(0.0 * mm, 0.0 * mm, 0.0 * mm);
#else
	G4ThreeVector originShift(10.0 * mm, GetGlobalOriginShiftY() * mm, 0.0 * mm);
	G4ThreeVector position(0.0 * mm, 0.0 * mm, 0.0 * mm);
#endif

	// ここで、イベント番号が0のときにoriginShiftの位置をログ出力（1 run内の最初のイベントのみ）
	if (anEvent->GetEventID() == 0) {
		G4cout << "Origin shift position: ("
			<< originShift.x() / mm << ", "
			<< originShift.y() / mm << ", "
			<< originShift.z() / mm << ") mm" << G4endl;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	// **α・β・γ の切り替え**
	////////////////////////////////////////////////////////////////////////////////////////
#ifdef SELECT_ALPHA
	// **α粒子 (238U系列) の照射設定**
	G4ParticleDefinition* ion = nullptr;

	// 238U をイオンとして設定
	ion = G4IonTable::GetIonTable()->GetIon(92, 238, 0.0);  // 238U
	fParticleGun->SetParticleDefinition(ion);

	if (!ion) {
		G4cerr << "Error: 238U not found in G4IonTable!" << G4endl;
	}

	/*
	// 追加: 238Uのプロセスマネージャに登録されているプロセスの出力
	G4ProcessManager* pmanager = ion->GetProcessManager();
	if (pmanager) {
		G4cout << "Process list for 238U:" << G4endl;
		pmanager->DumpInfo();
	}
	else {
		G4cerr << "Error: ProcessManager not found for 238U!" << G4endl;
	}
	*/

	// プライマリとしてはほぼゼロの運動エネルギーで生成
	particleEnergy = 0.0 * MeV;

	// **面線源（φ25mm）**
	G4double R = 12.5 * mm; // 半径12.5mm
	G4double r = R * std::sqrt(G4UniformRand());
	G4double theta = 2.0 * CLHEP::pi * G4UniformRand();
	G4ThreeVector localPosition(r * std::cos(theta), r * std::sin(theta), 0.0);
	position = originShift + localPosition;

#elif defined(SELECT_BETA)
	// **β粒子 (90Sr/90Y系列) の照射設定**
	G4ParticleDefinition* ion = nullptr;

	ion = G4IonTable::GetIonTable()->GetIon(38, 90, 0.0);  // 90Sr
	fParticleGun->SetParticleDefinition(ion);

	// プライマリとしてはほぼゼロの運動エネルギーで生成
	particleEnergy = 0.0 * MeV;

	// **面線源（φ5mm）**
	G4double R = 2.5 * mm; // 半径2.5mm
	G4double r = R * std::sqrt(G4UniformRand());
	G4double theta = 2.0 * CLHEP::pi * G4UniformRand();
	G4ThreeVector localPosition(r * std::cos(theta), r * std::sin(theta), 0.0);
	position = originShift + localPosition;

#elif defined(SELECT_GAMMA)
	// **γ線 (137Cs) の照射設定**
	G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	fParticleGun->SetParticleDefinition(particle);

	// **137Cs のγ線エネルギーを設定**
	particleEnergy = 0.662 * MeV;  // 137Cs の主な γ線エネルギー（661.657 keV）

	// 点線源なので、シフト分だけ移動するだけ
	position = originShift;

#endif

	// **共通の設定**
	fParticleGun->SetParticleEnergy(particleEnergy);
	fParticleGun->SetParticlePosition(position);


	// **等方的な放射（4π放射）**
	G4double cosTheta = 1.0 - 2.0 * G4UniformRand();
	G4double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
	G4double phi = 2.0 * CLHEP::pi * G4UniformRand();

	G4double dx = sinTheta * std::cos(phi);
	G4double dy = sinTheta * std::sin(phi);
	G4double dz = cosTheta;
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dx, dy, dz));

	/*
	// 固定方向 (0, 0, -1) を設定
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));
	*/


	// ここでプライマリ頂点を生成する
	fParticleGun->GeneratePrimaryVertex(anEvent);


	/*
	// **照射情報の出力**
	G4cout << "Particle: " << particleName
		<< ", Position: (" << position.x() / mm << ", " << position.y() / mm << ", " << position.z() / mm << ") mm"
		<< ", Energy: " << particleEnergy / MeV << " MeV" << G4endl;
	*/
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetOptPhotonPolar()
{
	G4double angle = G4UniformRand() * 360.0 * deg;
	SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
	if (fParticleGun->GetParticleDefinition() !=
		G4OpticalPhoton::OpticalPhotonDefinition())
	{
		G4ExceptionDescription ed;
		ed << "The particleGun is not an opticalphoton.";
		G4Exception("PrimaryGeneratorAction::SetOptPhotonPolar", "OpNovice2_004",
			JustWarning, ed);
		return;
	}

	fPolarized = true;
	fPolarization = angle;

	G4ThreeVector normal(1., 0., 0.);
	G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
	G4ThreeVector product = normal.cross(kphoton);
	G4double modul2 = product * product;

	G4ThreeVector e_perpend(0., 0., 1.);
	if (modul2 > 0.)
		e_perpend = (1. / std::sqrt(modul2)) * product;
	G4ThreeVector e_paralle = e_perpend.cross(kphoton);

	G4ThreeVector polar =
		std::cos(angle) * e_paralle + std::sin(angle) * e_perpend;
	fParticleGun->SetParticlePolarization(polar);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PrimaryGeneratorAction::SetRandomDirection(G4bool val)
{
	fRandomDirection = val;
}

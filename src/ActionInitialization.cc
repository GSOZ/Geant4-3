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
/// \file optical/OpNovice2/src/ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

// setter / getter �̎���
void ActionInitialization::SetPrimaryGenerator(PrimaryGeneratorAction* pg)
{
	fPrimaryGenerator = pg;
}

PrimaryGeneratorAction* ActionInitialization::GetPrimaryGenerator() const
{
	return fPrimaryGenerator;
}

ActionInitialization::ActionInitialization(DetectorConstruction* detector, const G4String& outputFileName)
	: G4VUserActionInitialization(),
	fDetector(detector),
	fOutputFileName(outputFileName),
	fPrimaryGenerator(nullptr) // ������nullptr
{}

void ActionInitialization::SetOutputFileName(const G4String& fname)
{
	fOutputFileName = fname;
}

void ActionInitialization::BuildForMaster() const
{
	// �}�X�^�[�p�ɂ́A�K�v�ɉ����ďo�̓t�@�C������n�� RunAction �𐶐�����
	SetUserAction(new RunAction(fOutputFileName));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
	// ���łɊO����PrimaryGeneratorAction���Z�b�g����Ă��邩�ǂ������m�F���A
	// �����Z�b�g����Ă��Ȃ���Γ����Ő�������
	if (!fPrimaryGenerator)
	{
		fPrimaryGenerator = new PrimaryGeneratorAction();
	}

	// �v���C�}��������
	auto primary = new PrimaryGeneratorAction();
	SetUserAction(primary);

	// �X�e�b�s���O�A�N�V�����̐����Ɠo�^
	auto steppingAction = new SteppingAction(fDetector);
	SetUserAction(steppingAction);

	// �����A�N�V����
	auto runAction = new RunAction(primary, steppingAction, fOutputFileName);
	SetUserAction(runAction);

	// TrackingAction�̓o�^
	SetUserAction(new TrackingAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

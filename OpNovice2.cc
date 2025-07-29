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

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "SteppingVerbose.hh"
#include "RunAction.hh"
#include "Run.hh"
#include <limits>

#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RunManagerFactory.hh"
#include "G4String.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

// ���[�h�I��
#define Interactive  // UI���g�������Ƃ��iSHIFTED_POSITION_MODE��OFF�ɂ���K�v����j
//#define SHIFTED_POSITION_MODE  // X�����ɂPmm�����炵���Ǝ˂��������Ƃ�


int main(int argc, char** argv)
{
	// --- ���[�U�[���́i�o�̓t�@�C�����A���s�񐔁A1�񂠂���̃C�x���g���j ---
	std::string outputFileName;
	std::cout << "�t�@�C����: ";
	std::cin >> outputFileName;

	int nEventsPerRun = 0;
	std::cout << "�Ǝˉ�: ";
	std::cin >> nEventsPerRun;

	int nRuns = 0;
	std::cout << "�J�Ԃ���: ";
	std::cin >> nRuns;



	// **SteppingVerbose ��K�p**
	SteppingVerbose* steppingVerbose = new SteppingVerbose();
	G4VSteppingVerbose::SetInstance(steppingVerbose);
	steppingVerbose->SetVerboseLevel(0);  // ���O��}��

	// **UI �̊m�F**
	G4UIExecutive* ui = nullptr;

#ifdef Interactive
	if (argc == 1)
		ui = new G4UIExecutive(argc, argv);
#endif

	// **RunManager �̍쐬**
	auto runManager = G4RunManagerFactory::CreateRunManager();

#ifdef G4MULTITHREADED
	// �}���`�X���b�h���[�h�̏ꍇ�́A���[�U�[�������O�ɃX���b�h����ݒ肷��
	runManager->SetNumberOfThreads(12); //�X���b�h���̎w�� 12����������
#endif

	// --- Detector, Physics, Action �̏����� ---
	auto detector = new DetectorConstruction();
	runManager->SetUserInitialization(detector);

	G4VModularPhysicsList* physicsList = new FTFP_BERT;
	physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
	physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());
	auto opticalPhysics = new G4OpticalPhysics();
	physicsList->RegisterPhysics(opticalPhysics);
	runManager->SetUserInitialization(physicsList);

	// ���d�q�j���[�g���m (anti_nu_e) �̃v���Z�X�𖳌���
	G4ParticleDefinition* antiNeutrino = G4ParticleTable::GetParticleTable()->FindParticle("anti_nu_e");
	if (antiNeutrino) {
		antiNeutrino->SetProcessManager(nullptr);
	}

	// ActionInitialization�̍쐬�i������RunAction�𐶐����A�o�̓t�@�C������ݒ肵�Ă���z��j
	ActionInitialization* actionInit = new ActionInitialization(detector, outputFileName);
	// �����Ń��\�b�h���Ăяo��
	actionInit->SetOutputFileName(outputFileName);
	runManager->SetUserInitialization(actionInit);

	// **�����̏�����**
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// **UI�}�l�[�W���[�������Ŏ擾����**
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// --- �o�b�`���[�h�ŃV�~�����[�V�������[�v�@������̃V�~�����[�V�������s���ꍇ�AUI���g�킸�Ƀ��[�v������BeamOn()���Ăяo��
	// �e run ���ŁA�ƎˈʒuX�� -10�`10 mm �͈̔́i1 mm ���݁j�ł��炵�Ȃ���V�~�����[�V���������s
#ifdef SHIFTED_POSITION_MODE
	for (int runIndex = 0; runIndex < nRuns; ++runIndex)
	{
		runManager->Initialize();
		G4cout << "Starting run " << (runIndex + 1) << " / " << nRuns << " (SHIFTED MODE)" << G4endl;

		// X���W�� -10 mm ���� 10 mm �܂� 1 mm ���݂ŕύX
		for (G4double yShift = 10.0; yShift >= -10.0; yShift -= 1.0)
		{
			// �ÓI�C���^�[�t�F�[�X���g���ăO���[�o���Ȍ��_�V�t�g�l���X�V����
			PrimaryGeneratorAction::SetGlobalOriginShiftY(yShift);

			G4cout << "  yShift = " << yShift << " mm" << G4endl;

			// �w�肳�ꂽ�Ǝˉ񐔕��̃C�x���g�����s
			runManager->BeamOn(nEventsPerRun);

			// �� �V�~�����[�V�������ʂ́ARunAction���̒��Ńt�@�C���o�͂����O��ł�
		}
		G4cout << "Finished run " << (runIndex + 1) << G4endl;
	}
#else
	// --- �]���̃��[�h ---
	if (!ui)
	{
		for (int i = 0; i < nRuns; ++i)
		{
			runManager->Initialize();
			G4cout << "Starting run " << (i + 1) << " / " << nRuns << G4endl;
			runManager->BeamOn(nEventsPerRun);
			G4cout << "Finished run " << (i + 1) << G4endl;
		}
	}
	else
	{
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
	}
#endif


	// **��n��**
	delete visManager;
	delete runManager;
	delete steppingVerbose;

	std::cout << "Press ENTER to exit." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}

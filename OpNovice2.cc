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

// モード選択
#define Interactive  // UIを使いたいとき（SHIFTED_POSITION_MODEもOFFにする必要あり）
//#define SHIFTED_POSITION_MODE  // X方向に１mmずつずらした照射をしたいとき


int main(int argc, char** argv)
{
	// --- ユーザー入力（出力ファイル名、試行回数、1回あたりのイベント数） ---
	std::string outputFileName;
	std::cout << "ファイル名: ";
	std::cin >> outputFileName;

	int nEventsPerRun = 0;
	std::cout << "照射回数: ";
	std::cin >> nEventsPerRun;

	int nRuns = 0;
	std::cout << "繰返し数: ";
	std::cin >> nRuns;



	// **SteppingVerbose を適用**
	SteppingVerbose* steppingVerbose = new SteppingVerbose();
	G4VSteppingVerbose::SetInstance(steppingVerbose);
	steppingVerbose->SetVerboseLevel(0);  // ログを抑制

	// **UI の確認**
	G4UIExecutive* ui = nullptr;

#ifdef Interactive
	if (argc == 1)
		ui = new G4UIExecutive(argc, argv);
#endif

	// **RunManager の作成**
	auto runManager = G4RunManagerFactory::CreateRunManager();

#ifdef G4MULTITHREADED
	// マルチスレッドモードの場合は、ユーザー初期化前にスレッド数を設定する
	runManager->SetNumberOfThreads(12); //スレッド数の指定 12がいい感じ
#endif

	// --- Detector, Physics, Action の初期化 ---
	auto detector = new DetectorConstruction();
	runManager->SetUserInitialization(detector);

	G4VModularPhysicsList* physicsList = new FTFP_BERT;
	physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
	physicsList->RegisterPhysics(new G4RadioactiveDecayPhysics());
	auto opticalPhysics = new G4OpticalPhysics();
	physicsList->RegisterPhysics(opticalPhysics);
	runManager->SetUserInitialization(physicsList);

	// 反電子ニュートリノ (anti_nu_e) のプロセスを無効化
	G4ParticleDefinition* antiNeutrino = G4ParticleTable::GetParticleTable()->FindParticle("anti_nu_e");
	if (antiNeutrino) {
		antiNeutrino->SetProcessManager(nullptr);
	}

	// ActionInitializationの作成（内部でRunActionを生成し、出力ファイル名を設定している想定）
	ActionInitialization* actionInit = new ActionInitialization(detector, outputFileName);
	// ここでメソッドを呼び出す
	actionInit->SetOutputFileName(outputFileName);
	runManager->SetUserInitialization(actionInit);

	// **可視化の初期化**
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// **UIマネージャーをここで取得する**
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// --- バッチモードでシミュレーションループ　複数回のシミュレーションを行う場合、UIを使わずにループ処理でBeamOn()を呼び出す
	// 各 run 内で、照射位置Xを -10～10 mm の範囲（1 mm 刻み）でずらしながらシミュレーションを実行
#ifdef SHIFTED_POSITION_MODE
	for (int runIndex = 0; runIndex < nRuns; ++runIndex)
	{
		runManager->Initialize();
		G4cout << "Starting run " << (runIndex + 1) << " / " << nRuns << " (SHIFTED MODE)" << G4endl;

		// X座標を -10 mm から 10 mm まで 1 mm 刻みで変更
		for (G4double yShift = 10.0; yShift >= -10.0; yShift -= 1.0)
		{
			// 静的インターフェースを使ってグローバルな原点シフト値を更新する
			PrimaryGeneratorAction::SetGlobalOriginShiftY(yShift);

			G4cout << "  yShift = " << yShift << " mm" << G4endl;

			// 指定された照射回数分のイベントを実行
			runManager->BeamOn(nEventsPerRun);

			// ※ シミュレーション結果は、RunAction等の中でファイル出力される前提です
		}
		G4cout << "Finished run " << (runIndex + 1) << G4endl;
	}
#else
	// --- 従来のモード ---
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


	// **後始末**
	delete visManager;
	delete runManager;
	delete steppingVerbose;

	std::cout << "Press ENTER to exit." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}

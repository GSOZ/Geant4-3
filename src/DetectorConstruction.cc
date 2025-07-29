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
/// \file optical/OpNovice2/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//


#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericTrap.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"

///////////////////////////////////////////////////////////////////////////////////////////
//モード切替え
//#define SCINTILLATOR
#define TEST_IRRADIATION

//照射モード切替（PrimaryGeneratorAction.cc側も切り替えること）
//#define ALPHA
//#define BETA
#define GAMMA
///////////////////////////////////////////////////////////////////////////////////////////

DetectorConstruction::DetectorConstruction()
	: G4VUserDetectorConstruction()
	, fDetectorMessenger(nullptr)
{
	fWorldMPT = new G4MaterialPropertiesTable();
	fTankMPT = new G4MaterialPropertiesTable();
	fTankMPT2 = new G4MaterialPropertiesTable();
	fTankMPTPET = new G4MaterialPropertiesTable();
	fTankMPT3 = new G4MaterialPropertiesTable();
	fTankMPT4 = new G4MaterialPropertiesTable();
	fTankMPTGr = new G4MaterialPropertiesTable();
	fTankMPTG = new G4MaterialPropertiesTable();
	fReflectorMPT = new G4MaterialPropertiesTable();

	fSurfaceMPT = new G4MaterialPropertiesTable();
	fSurfaceMPT2 = new G4MaterialPropertiesTable();
	fSurfaceMPTPET = new G4MaterialPropertiesTable();
	fSurfaceMPT3 = new G4MaterialPropertiesTable();
	fSurfaceMPT4 = new G4MaterialPropertiesTable();
	fSurfaceMPTGr = new G4MaterialPropertiesTable();
	fSurfaceMPTG = new G4MaterialPropertiesTable();
	fSurfaceMPTR = new G4MaterialPropertiesTable();

	G4NistManager* nistManager = G4NistManager::Instance();
	G4Element* Gd = nistManager->FindOrBuildElement("Gd");
	G4Element* Si = nistManager->FindOrBuildElement("Si");

	G4Element* Zn = new G4Element("Zinc", "Zn", 30., 65.38 * g / mole);
	G4Element* S = new G4Element("Sulfur", "S", 16., 32.065 * g / mole);
	G4Element* C = new G4Element("Carbon", "C", 6., 12.01 * g / mole);
	G4Element* H = new G4Element("Hydrogen", "H", 1., 1.008 * g / mole);
	G4Element* O = new G4Element("Oxygen", "O", 8., 16.00 * g / mole);

	G4double density = 4.09 * g / cm3;
	fTankMaterial2 = new G4Material("ZnS", density, 2);
	fTankMaterial2->AddElement(Zn, 1);
	fTankMaterial2->AddElement(S, 1);

	G4double PETdensity = 1.38 * g / cm3;
	fTankMaterialPET = new G4Material("PET", PETdensity, 3);
	fTankMaterialPET->AddElement(C, 10);
	fTankMaterialPET->AddElement(H, 8);
	fTankMaterialPET->AddElement(O, 4);

	G4double plasticDensity = 1.032 * g / cm3;
	fTankMaterial3 = new G4Material("Plastic", plasticDensity, 2);
	fTankMaterial3->AddElement(C, 9);
	fTankMaterial3->AddElement(H, 10);

	G4double GSODensity = 6.71 * g / cm3;
	fTankMaterial4 = new G4Material("GSO", GSODensity, 3);
	fTankMaterial4->AddElement(Gd, 2);
	fTankMaterial4->AddElement(Si, 1);
	fTankMaterial4->AddElement(O, 5);


	// ここで、TEST_IRRADIATION モードかつ GAMMA モードの場合のみ、検出器材質を γ線吸収性の高いなまりに変更する
#ifdef SCINTILLATOR
	fTankMaterial = new G4Material("GSO", GSODensity, 3);
	fTankMaterial->AddElement(Gd, 2);
	fTankMaterial->AddElement(Si, 1);
	fTankMaterial->AddElement(O, 5);

#elif defined(TEST_IRRADIATION)
#if defined(ALPHA) || defined(BETA)
	fTankMaterial = new G4Material("GSO", GSODensity, 3);
	fTankMaterial->AddElement(Gd, 2);
	fTankMaterial->AddElement(Si, 1);
	fTankMaterial->AddElement(O, 5);

#elif defined(GAMMA)
	fTankMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");

#endif
#endif

	G4double GreaseDensity = 1.0 * g / cm3;
	fTankMaterialGr = new G4Material("Grease", GreaseDensity, 2);
	fTankMaterialGr->AddElement(C, 9);
	fTankMaterialGr->AddElement(H, 10);

	G4double GuideDensity = 1.032 * g / cm3;
	fTankMaterialG = new G4Material("Guide", GuideDensity, 2);
	fTankMaterialG->AddElement(C, 9);
	fTankMaterialG->AddElement(H, 10);

	fTankMaterialR = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
	fWorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction() {
	delete fTankMPT;
	delete fTankMPT2;
	delete fTankMPTPET;
	delete fTankMPT3;
	delete fTankMPT4;
	delete fTankMPTGr;
	delete fTankMPTG;
	delete fWorldMPT;
	delete fSurfaceMPT;
	delete fSurfaceMPT2;
	delete fSurfaceMPTPET;
	delete fSurfaceMPT3;
	delete fSurfaceMPT4;
	delete fSurfaceMPTG;
	delete fSurface;
	delete fDetectorMessenger;
	delete SurfaceZnSPlastic;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	const G4int nEntries = 2;
	G4double PhotonEnergy[nEntries] = { 1.24 * eV, 3.1 * eV };
	//G4double abslength[nEntries] = {44.81*cm, 44.81*cm};

	fWorldMaterial->SetMaterialPropertiesTable(fWorldMPT);
	fTankMaterial->SetMaterialPropertiesTable(fTankMPT);
	//fTankMaterial->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
	fTankMaterial2->SetMaterialPropertiesTable(fTankMPT2);
	fTankMaterial2->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterialPET->SetMaterialPropertiesTable(fTankMPTPET);
	fTankMaterialPET->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterial3->SetMaterialPropertiesTable(fTankMPT3);
	fTankMaterial3->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterial4->SetMaterialPropertiesTable(fTankMPT4);
	fTankMaterial4->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterialGr->SetMaterialPropertiesTable(fTankMPTGr);
	fTankMaterialGr->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterialG->SetMaterialPropertiesTable(fTankMPTG);
	fTankMaterialG->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);
	fTankMaterialR->SetMaterialPropertiesTable(fReflectorMPT);
	//fTankMaterialR->GetIonisation()->SetBirksConstant(0.01 * mm / MeV);


	// ------------- Volumes --------------
	// Position Control
	G4double height_ZnS = (fTankRZnSout_z * 2) + fTank2_z;
	G4double height_PET = height_ZnS + fTank2_z + fTankPET_z;
	G4double height_Gre_PETPla = height_PET + fTankPET_z + Greese_z;
	G4double height_Plastic = height_Gre_PETPla + Greese_z + fTank3_z;
	G4double height_Gre_PlaGSO = height_Plastic + fTank3_z + Greese_z;
	G4double height_GSO = height_Gre_PlaGSO + Greese_z + fTank4_z;
	G4double height_Gre_GSOGuide = height_GSO + fTank4_z + Greese_z;
	G4double GuideLength = 15 * mm;  // GuideLength_adjust
	G4double height_Guide = height_Gre_GSOGuide + Greese_z + (GuideLength / 2);
	G4double height_Gre_GuideDET = height_Guide + (GuideLength / 2) + Greese_z;
	G4double height_DET = height_Gre_GuideDET + Greese_z + fTank_z;
	G4double height_Ref_GSO = fTankRGSOout_z;

	// World
	auto world_box = new G4Box("World", fExpHall_x, fExpHall_y, fExpHall_z);
	fWorld_LV = new G4LogicalVolume(world_box, fWorldMaterial, "World");
	G4VPhysicalVolume* world_PV = new G4PVPlacement(nullptr, G4ThreeVector(), fWorld_LV, "World", nullptr, false, 0);


#ifdef SCINTILLATOR
	// Rleflector_ZnS
	auto Ring_Box = new G4Box("Tank_ZnS", fTankRZnSout_x, fTankRZnSout_y, fTankRZnSout_z);
	RingBox_LV = new G4LogicalVolume(Ring_Box, fTankMaterialR, "RingBox_ZnSLV");
	RingBox = new G4PVPlacement(0, G4ThreeVector(0, 0, -fTankRZnSout_z * mm), RingBox_LV, "RingBox_ZnSLV", fWorld_LV, false, 0);

	// The tank2 (ZnS)
	auto tank_box2 = new G4Box("Tank_ZnS", fTank2_x, fTank2_y, fTank2_z);
	fTank2_LV = new G4LogicalVolume(tank_box2, fTankMaterial2, "Tank_ZnS");
	fTank2 = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_ZnS * mm), fTank2_LV, "Tank_ZnS", fWorld_LV, false, 0);

	// The tankPET
	auto tank_boxPET = new G4Box("Tank_ZnS", fTankPET_x, fTankPET_y, fTankPET_z);
	fTankPET_LV = new G4LogicalVolume(tank_boxPET, fTankMaterialPET, "Tank_PET");
	fTankPET = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_PET * mm), fTankPET_LV, "Tank_PET", fWorld_LV, false, 0);

	// The tank3 (Plastic)
	auto tank_box3 = new G4Box("Tank_Plastic", fTank3_x, fTank3_y, fTank3_z);
	fTank3_LV = new G4LogicalVolume(tank_box3, fTankMaterial3, "Tank_Plastic");
	fTank3 = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Plastic * mm), fTank3_LV, "Tank_Plastic", fWorld_LV, false, 0);

	/*
	//GSOケース
	auto fTankGSO16in = new G4Box("GSOInBox", fTank4_x, fTank4_y, fTank4_z); // GSO本体

	//GSOとくり抜き箇所の管理リスト
	std::vector<G4ThreeVector> holePositions = {
		G4ThreeVector(-fTank4_xGap, -fTank4_yGap, -height_GSO * mm),
		G4ThreeVector(fTank4_xGap, -fTank4_yGap, -height_GSO * mm),
		G4ThreeVector(-fTank4_xGap, fTank4_yGap, -height_GSO * mm),
		G4ThreeVector(fTank4_xGap, fTank4_yGap, -height_GSO * mm),
		G4ThreeVector(-fTank4_xGap, -(fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(fTank4_xGap, -(fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(-fTank4_xGap, (fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(fTank4_xGap, (fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(-(fTank4_xGap * 3), -(fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector((fTank4_xGap * 3), -(fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(-(fTank4_xGap * 3), (fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector((fTank4_xGap * 3), (fTank4_yGap * 3), -height_GSO * mm),
		G4ThreeVector(-(fTank4_xGap * 3), -fTank4_yGap, -height_GSO * mm),
		G4ThreeVector((fTank4_xGap * 3), -fTank4_yGap, -height_GSO * mm),
		G4ThreeVector(-(fTank4_xGap * 3), fTank4_yGap, -height_GSO * mm),
		G4ThreeVector((fTank4_xGap * 3), fTank4_yGap, -height_GSO * mm)
	};

	// GSO論理ボリューム作成＋16本の実装
	G4LogicalVolume* fTank4_LV = new G4LogicalVolume(fTankGSO16in, fTankMaterial4, "Tank_GSOa");
	for (const auto& pos : holePositions) {
		new G4PVPlacement(0, pos, fTank4_LV, "Tank_GSO", fWorld_LV, false, 0);
	}

	// Reflector_GSO
	auto fTankRGSOout = new G4Box("GSOOutBox", fTankRGSOout_x, fTankRGSOout_y, fTankRGSOout_z);
	auto fTankRGSOin = new G4Box("GSOInBox", fTankRGSOin_x, fTankRGSOin_y, fTankRGSOin_z);
	auto GSORing_Box = new G4SubtractionSolid("GSORing_Box", fTankRGSOout, fTankRGSOin);
	GSORingBox_LV = new G4LogicalVolume(GSORing_Box, fTankMaterialR, "GSORingBox_LV");
	GSORingBox = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Ref_GSO * mm), GSORingBox_LV, "GSORingBox_LV", fWorld_LV, false, 0);

	// Grease
	// グリス層のサイズ定義
	auto GreaseGrid_x = new G4Box("GreaseGrid_x", GreeseGrid_x, GreeseGrid_y, fTank4_z);
	auto GreaseGrid_y = new G4Box("GreaseGrid_y", GreeseGrid_y, GreeseGrid_x, fTank4_z);

	// G4UnionSolidによるGSOグリッド
	// X方向のGSOグリッド板の位置を個々に定義
	std::vector<G4ThreeVector> positions_x = {
		G4ThreeVector(0, fTank4_yGap * 4, 0 * mm),
		G4ThreeVector(0, fTank4_yGap * 2, 0 * mm),
		//G4ThreeVector(0, fTank4_yGap * 2, 0 * mm),  中央位置は GreaseGridUnion_xの初期設定時に原点に１個作られてしまうため省略
		G4ThreeVector(0, -fTank4_yGap * 2, 0 * mm),
		G4ThreeVector(0, -fTank4_yGap * 4, 0 * mm)
	};

	// Y方向のGSOグリッド板の位置管理
	std::vector<G4ThreeVector> positions_y = {
		G4ThreeVector(fTank4_xGap * 4, 0, 0 * mm),
		G4ThreeVector(fTank4_xGap * 2, 0, 0 * mm),
		//G4ThreeVector(0, fTank4_yGap * 2, 0 * mm),  中央位置は GreaseGridUnion_xの初期設定時に原点に１個作られてしまうため省略
		G4ThreeVector(-fTank4_xGap * 2, 0, 0 * mm),
		G4ThreeVector(-fTank4_xGap * 4, 0, 0 * mm)
	};

	// GreaseGridUnionを初期化＋Forループで追加
	G4UnionSolid* GreaseGridUnion = new G4UnionSolid("GreaseGridUnion_x1", GreaseGrid_x, GreaseGrid_x, 0, positions_x[0]);
	for (size_t i = 1; i < positions_x.size(); ++i) {
		GreaseGridUnion = new G4UnionSolid("GreaseGridUnion_x" + std::to_string(i + 1), GreaseGridUnion, GreaseGrid_x, 0, positions_x[i]);
	}

	// Y方向のグリッドをGreaseGridUnionに直接追加
	for (size_t i = 0; i < positions_y.size(); ++i) {
		GreaseGridUnion = new G4UnionSolid("GreaseGridUnion_xy" + std::to_string(i + 1), GreaseGridUnion, GreaseGrid_y, 0, positions_y[i]);
	}

	G4LogicalVolume* GreaseGSOx_LV = new G4LogicalVolume(GreaseGridUnion, fTankMaterialGr, "GreaseGSO_LV");
	new G4PVPlacement(0, G4ThreeVector(0, 0, -height_GSO * mm), GreaseGSOx_LV, "GreaseGridUnion_x", fWorld_LV, false, 0);

	auto Grease = new G4Box("Grease", fTank3_x + 0.01, fTank3_y + 0.01, Greese_z);
	Grease_LV = new G4LogicalVolume(Grease, fTankMaterialGr, "Grease_LV");
	Grease_LV2 = new G4LogicalVolume(Grease, fTankMaterialGr, "Grease_LV");

	//干渉部分があるGSOグリッド
	GreaseGSOx_LV = new G4LogicalVolume(GreaseGrid_x, fTankMaterialR, "GreaseGSO_LV");
	GreaseGSOy_LV = new G4LogicalVolume(GreaseGrid_y, fTankMaterialR, "GreaseGSO_LV");

	GreaseGSO_x1 = new G4PVPlacement(0, G4ThreeVector(0, (fTank4_yGap * 4), -height_GSO * mm), GreaseGSOx_LV, "GreaseGSO_x1", fWorld_LV, false, 0);
	GreaseGSO_x2 = new G4PVPlacement(0, G4ThreeVector(0, (fTank4_yGap * 2), -height_GSO * mm), GreaseGSOx_LV, "GreaseGSO_x2", fWorld_LV, false, 0);
	GreaseGSO_x3 = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_GSO * mm), GreaseGSOx_LV, "GreaseGSO_x3", fWorld_LV, false, 0);
	GreaseGSO_x4 = new G4PVPlacement(0, G4ThreeVector(0, -(fTank4_yGap * 2), -height_GSO * mm), GreaseGSOx_LV, "GreaseGSO_x4", fWorld_LV, false, 0);
	GreaseGSO_x5 = new G4PVPlacement(0, G4ThreeVector(0, -(fTank4_yGap * 4), -height_GSO * mm), GreaseGSOx_LV, "GreaseGSO_x5", fWorld_LV, false, 0);

	GreaseGSO_y1 = new G4PVPlacement(0, G4ThreeVector((fTank4_xGap * 4), 0, -height_GSO * mm), GreaseGSOy_LV, "GreaseGSO_y1", fWorld_LV, false, 0);
	GreaseGSO_y2 = new G4PVPlacement(0, G4ThreeVector((fTank4_xGap * 2), 0, -height_GSO * mm), GreaseGSOy_LV, "GreaseGSO_y2", fWorld_LV, false, 0);
	GreaseGSO_y3 = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_GSO * mm), GreaseGSOy_LV, "GreaseGSO_y3", fWorld_LV, false, 0);
	GreaseGSO_y4 = new G4PVPlacement(0, G4ThreeVector(-(fTank4_xGap * 2), 0, -height_GSO * mm), GreaseGSOy_LV, "GreaseGSO_y4", fWorld_LV, false, 0);
	GreaseGSO_y5 = new G4PVPlacement(0, G4ThreeVector(-(fTank4_xGap * 4), 0, -height_GSO * mm), GreaseGSOy_LV, "GreaseGSO_y5", fWorld_LV, false, 0);

	GreasePETPla = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Gre_PETPla * mm), Grease_LV, "Grease_PlaGSO", fWorld_LV, false, 0);
	GreasePlaGSO = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Gre_PlaGSO * mm), Grease_LV2, "Grease_PlaGSO", fWorld_LV, false, 0);
	GreaseGSOGuide = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Gre_GSOGuide * mm), Grease_LV, "Grease_GSOGuide", fWorld_LV, false, 0);
	*/

	// Guide
	G4double bottomX = 5.00 * mm;
	G4double bottomY = 5.00 * mm;
	G4double topX = 10.00 * mm;
	G4double topY = 10.00 * mm;

	std::vector<G4TwoVector> vertices;
	vertices.push_back(G4TwoVector(-bottomX / 2, -bottomY / 2));
	vertices.push_back(G4TwoVector(-bottomX / 2, bottomY / 2));
	vertices.push_back(G4TwoVector(bottomX / 2, bottomY / 2));
	vertices.push_back(G4TwoVector(bottomX / 2, -bottomY / 2));
	vertices.push_back(G4TwoVector(-topX / 2, -topY / 2));
	vertices.push_back(G4TwoVector(-topX / 2, topY / 2));
	vertices.push_back(G4TwoVector(topX / 2, topY / 2));
	vertices.push_back(G4TwoVector(topX / 2, -topY / 2));

	auto tank_boxG = new G4GenericTrap("Tank_Guide", GuideLength / 2, vertices);
	fTankG_LV = new G4LogicalVolume(tank_boxG, fTankMaterialG, "Tank_Guide");
	fTankG = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Guide * mm), fTankG_LV, "Tank_Guide", fWorld_LV, false, 0);

	// Guide_Reflector
	G4double bottomXRefOut = bottomX + 0.4 * mm;
	G4double bottomYRefOut = bottomY + 0.4 * mm;
	G4double topXRefOut = topX + 0.4 * mm;
	G4double topYRefOut = topY + 0.4 * mm;
	G4double heightRefOut = GuideLength + 0.01 * mm;
	std::vector<G4TwoVector> verticesRefOut;
	verticesRefOut.push_back(G4TwoVector(-bottomXRefOut / 2, -bottomYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(-bottomXRefOut / 2, bottomYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(bottomXRefOut / 2, bottomYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(bottomXRefOut / 2, -bottomYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(-topXRefOut / 2, -topYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(-topXRefOut / 2, topYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(topXRefOut / 2, topYRefOut / 2));
	verticesRefOut.push_back(G4TwoVector(topXRefOut / 2, -topYRefOut / 2));

	G4double bottomXRefIn = bottomX + 0.01 * mm;
	G4double bottomYRefIn = bottomY + 0.01 * mm;
	G4double topXRefIn = topX + 0.02 * mm;
	G4double topYRefIn = topY + 0.02 * mm;
	G4double heightRefIn = GuideLength + 0.015 * mm;

	std::vector<G4TwoVector> verticesRefIn;
	verticesRefIn.push_back(G4TwoVector(-bottomXRefIn / 2, -bottomYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(-bottomXRefIn / 2, bottomYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(bottomXRefIn / 2, bottomYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(bottomXRefIn / 2, -bottomYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(-topXRefIn / 2, -topYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(-topXRefIn / 2, topYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(topXRefIn / 2, topYRefIn / 2));
	verticesRefIn.push_back(G4TwoVector(topXRefIn / 2, -topYRefIn / 2));

	auto reflectorOut = new G4GenericTrap("ReflectorOut", heightRefOut / 2, verticesRefOut);
	auto reflectorIn = new G4GenericTrap("ReflectorIn", heightRefIn / 2, verticesRefIn);
	auto RefPlastic = new G4SubtractionSolid("RefPlastic", reflectorOut, reflectorIn);
	reflector_LV = new G4LogicalVolume(RefPlastic, fTankMaterialR, "ReflectorPla");
	fTankRPla = new G4PVPlacement(0, G4ThreeVector(0, 0, -(height_Guide + 0.005) * mm), reflector_LV, "ReflectorPla", fWorld_LV, false, 0);


	// Grease_Guide_Detector
	auto Grease2 = new G4Box("Grease", bottomX / 2, bottomY / 2, 0.005);
	Grease_LV3 = new G4LogicalVolume(Grease2, fTankMaterialGr, "Grease_LV3");
	GreaseGuideDET = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_Gre_GuideDET * mm), Grease_LV3, "Grease_GSOGuide", fWorld_LV, false, 0);

	// Detector
	G4double innerRadius = 0.0 * mm;
	G4double outerRadius = 4 * mm;
	G4double height = 1.0 * mm;
	G4double startAngle = 0.0 * deg;
	G4double spanningAngle = 360.0 * deg;

	auto tank_box = new G4Tubs("Tank", innerRadius, outerRadius, height, startAngle, spanningAngle);
	fTank_LV = new G4LogicalVolume(tank_box, fTankMaterial, "Tank");
	fTank = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_DET * mm), fTank_LV, "Tank", fWorld_LV, false, 0);

	/*
	// Reflector_Detector
	auto DETRing_Box = new G4Tubs("DETRing_Box", innerRadius, outerRadius, height, startAngle, spanningAngle);
	auto DETRefrector = new G4Box("DETReflector", fTankG_x + 0.2, fTankG_y + 0.2, height);
	auto DETReflectorBox = new G4SubtractionSolid("DETReflectorBox", DETRefrector, DETRing_Box, 0, G4ThreeVector());
	DETRingBox_LV = new G4LogicalVolume(DETReflectorBox, fTankMaterialR, "DETRingBox_LV");
	DETRingBox = new G4PVPlacement(0, G4ThreeVector(0, 0, -height_DET * mm), DETRingBox_LV, "DETRingBox_LV", fWorld_LV, false, 0);
	*/
#endif

#ifdef TEST_IRRADIATION
	////////////////////////////////////////////////////////////////////////////////////
	// 線源アルミ膜
	////////////////////////////////////////////////////////////////////////////////////

	G4double foil2_r = 12.5 * mm;  // 半径 (φ25mmなので12.5mm)

#ifdef ALPHA
	G4double foil2_z = 1 * mm;     // α線源用厚み
	G4double sourceFoil_Z = (foil2_z / 2) + 0.06 * mm;  // α用のZ位置

#elif defined(BETA)
	G4double foil2_z = 0.0185 * mm;     // β線源用厚み
	G4double sourceFoil_Z = -(foil2_z / 2) - 0.01 * mm;  // β用のZ位置

#elif defined(GAMMA)
	G4double foil2_z = 4 * mm;  // γ線用厚み（4mm）
	G4double sourceFoil_Z = -(foil2_z / 2) - 0.01 * mm;  // γ線源のすぐ下に配置

#else
#error "線源の種類 (ALPHA_SOURCE or BETA_SOURCE) を定義してください"

#endif


	G4Material* aluminum2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");  	// アルミニウム材質を取得
	auto foil_tube2 = new G4Tubs("AluminumFoil", 0, foil2_r, foil2_z / 2, 0.0 * deg, 360.0 * deg);  	// アルミニウム膜の円柱形状
	auto foil_LV2 = new G4LogicalVolume(foil_tube2, aluminum2, "AluminumFoil");  	// 膜のロジカルボリューム
	new G4PVPlacement(0, G4ThreeVector(0, 0, sourceFoil_Z), foil_LV2, "AluminumFoil", fWorld_LV, false, 0);  	// 配置（Tankの上面に配置）



	////////////////////////////////////////////////////////////////////////////////////
	// Detector
	////////////////////////////////////////////////////////////////////////////////////

	G4double tank_x = 10.0 * mm;
	G4double tank_y = 10.0 * mm;
	G4double tank_z = 3.0 * mm;

#ifdef GAMMA
	tank_z = 10.0 * mm;  // ガンマ線の場合の厚み変更
#endif


	auto tank_box = new G4Box("Tank", tank_x / 2, tank_y / 2, tank_z / 2);
	fTank_LV = new G4LogicalVolume(tank_box, fTankMaterial, "Tank");

#ifdef ALPHA
	G4double detector_Z = -1.278 * mm - (tank_z / 2);  // α線用のZ位置

#elif defined(BETA)
	G4double detector_Z = -2.2965 * mm - (tank_z / 2);  // β線用のZ位置

#elif defined(GAMMA)
	G4double detector_Z = -(37.278 * mm + (tank_z / 2));  // γ線用のZ位置

#else
#error "#define（ALPHA, BETA, GAMMA）を定義してください"

#endif

	// 配置位置の調整（中央配置）
	fTank = new G4PVPlacement(0, G4ThreeVector(0, 0, detector_Z * mm), fTank_LV, "Tank", fWorld_LV, false, 0);


	////////////////////////////////////////////////////////////////////////////////////
	// ZnSのPET (BETA または GAMMA の場合のみ)
	////////////////////////////////////////////////////////////////////////////////////

	G4double frame2_x = 10.0 * mm;
	G4double frame2_y = 10.0 * mm;

#ifdef BETA
	G4double frame2_z = 0.25 * mm;   // BETA の場合、元の厚さ 0.25mm

#elif defined(GAMMA)
	G4double frame2_z = 15.25 * mm;  // GAMMA の場合、厚さ 15.25mm

#endif

#if defined(BETA) || defined(GAMMA)
	// ABS素材を取得
	G4Material* absMaterial2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

	// 外枠
	auto frame_box2 = new G4Box("FrameOuter", frame2_x / 2, frame2_y / 2, frame2_z / 2);

	// フレームのロジカルボリューム
	auto frame_LV2 = new G4LogicalVolume(frame_box2, absMaterial2, "Frame");

	// ----- 配置（Detector の上に配置） -----
	G4double frame2_Z = detector_Z + (tank_z / 2) + (frame2_z / 2);
	new G4PVPlacement(0, G4ThreeVector(0, 0, frame2_Z), frame_LV2, "Frame", fWorld_LV, false, 0);
#endif


	////////////////////////////////////////////////////////////////////////////////////
	// アルミ膜 (ALPHA, BETA, GAMMA の場合)
	////////////////////////////////////////////////////////////////////////////////////

	G4double foil_x = 10.0 * mm;
	G4double foil_y = 10.0 * mm;
	G4double foil_z = 0.008 * mm;

	// アルミニウム材質を取得（Geant4のNISTマテリアル）
	G4Material* aluminum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");

	// アルミニウム膜のボックス形状
	auto foil_box = new G4Box("AluminumFoil", foil_x / 2, foil_y / 2, foil_z / 2);
	auto foil_LV = new G4LogicalVolume(foil_box, aluminum, "AluminumFoil");

	G4double aluminumFoil_Z;

#ifdef ALPHA
	// ALPHA の場合 → Detector のすぐ上
	aluminumFoil_Z = detector_Z + (tank_z / 2) + (foil_z / 2);

#elif defined(BETA) || defined(GAMMA)
	// BETA, GAMMA の場合 → ZnSのPET の上
	aluminumFoil_Z = frame2_Z + (frame2_z / 2) + (foil_z / 2);

#endif

	// ----- 配置 -----
	new G4PVPlacement(0, G4ThreeVector(0, 0, aluminumFoil_Z), foil_LV, "AluminumFoil", fWorld_LV, false, 0);

	////////////////////////////////////////////////////////////////////////////////////
	// フレーム (ALPHA, BETA, GAMMA いずれの場合も配置)
	////////////////////////////////////////////////////////////////////////////////////
#if defined(ALPHA) || defined(BETA) || defined(GAMMA)

	G4double frame_x = 15.0 * mm;
	G4double frame_y = 15.0 * mm;
	G4double frame_z = 1.0 * mm;

	// 中央の穴のサイズ
	G4double hole_x = 10.0 * mm;
	G4double hole_y = 10.0 * mm;
	G4double hole_z = 1.0 * mm;

	// ABS素材を取得
	G4Material* absMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

	// 外枠
	auto frame_box = new G4Box("FrameOuter", frame_x / 2, frame_y / 2, frame_z / 2);

	// 中央の穴
	auto frame_hole = new G4Box("FrameHole", hole_x / 2, hole_y / 2, hole_z / 2);

	// 外枠から穴を削除
	auto frame_shape = new G4SubtractionSolid("Frame", frame_box, frame_hole, 0, G4ThreeVector(0, 0, 0));

	// フレームのロジカルボリューム
	auto frame_LV = new G4LogicalVolume(frame_shape, absMaterial, "Frame");

	// ----- 配置（アルミ膜の上に配置） -----
	G4double frame_Z = aluminumFoil_Z + (foil_z / 2) + (frame_z / 2);  // 修正: foil_z / 2 を追加
	new G4PVPlacement(0, G4ThreeVector(0, 0, frame_Z), frame_LV, "Frame", fWorld_LV, false, 0);

#endif
#endif

	// ------------- Surface --------------
	fSurface = new G4OpticalSurface("Surface");
	fSurface->SetType(dielectric_dielectric);
	fSurface->SetFinish(ground);
	fSurface->SetModel(unified);
	fSurface->SetMaterialPropertiesTable(fSurfaceMPT);
	auto surface = new G4LogicalBorderSurface("Surface", fTank, world_PV, fSurface);
	auto opticalSurface = dynamic_cast<G4OpticalSurface*>(surface->GetSurface(fTank, world_PV)->GetSurfaceProperty());

	fSurface2 = new G4OpticalSurface("Surface2");
	fSurface2->SetType(dielectric_dielectric);
	fSurface2->SetFinish(ground);
	fSurface2->SetModel(unified);
	fSurface2->SetMaterialPropertiesTable(fSurfaceMPT2);
	auto surface2 = new G4LogicalBorderSurface("Surface2", fTank2, world_PV, fSurface2);
	auto opticalSurface2 = dynamic_cast<G4OpticalSurface*>(surface2->GetSurface(fTank2, world_PV)->GetSurfaceProperty());

	fSurfacePET = new G4OpticalSurface("SurfacePET");
	fSurfacePET->SetType(dielectric_dielectric);
	fSurfacePET->SetFinish(ground);
	fSurfacePET->SetModel(unified);
	fSurfacePET->SetMaterialPropertiesTable(fSurfaceMPTPET);
	auto surfacePET = new G4LogicalBorderSurface("SurfacePET", fTankPET, world_PV, fSurfacePET);
	auto opticalSurfacePET = dynamic_cast<G4OpticalSurface*>(surfacePET->GetSurface(fTankPET, world_PV)->GetSurfaceProperty());

	fSurface3 = new G4OpticalSurface("Surface3");
	fSurface3->SetType(dielectric_dielectric);
	fSurface3->SetFinish(ground);
	fSurface3->SetModel(unified);
	fSurface3->SetMaterialPropertiesTable(fSurfaceMPT3);
	auto surface3 = new G4LogicalBorderSurface("Surface3", fTank3, world_PV, fSurface3);
	auto opticalSurface3 = dynamic_cast<G4OpticalSurface*>(surface3->GetSurface(fTank3, world_PV)->GetSurfaceProperty());

	fSurface4 = new G4OpticalSurface("Surface4");
	fSurface4->SetType(dielectric_dielectric);
	fSurface4->SetFinish(ground);
	fSurface4->SetModel(unified);
	fSurface4->SetMaterialPropertiesTable(fSurfaceMPT4);
	auto surface4a = new G4LogicalBorderSurface("Surface4a", fTank4a, world_PV, fSurface4);
	auto opticalSurface4a = dynamic_cast<G4OpticalSurface*>(surface4a->GetSurface(fTank4a, world_PV)->GetSurfaceProperty());

	fSurfaceGr = new G4OpticalSurface("SurfaceGr");
	fSurfaceGr->SetType(dielectric_dielectric);
	fSurfaceGr->SetFinish(ground);
	fSurfaceGr->SetModel(unified);
	fSurfaceGr->SetMaterialPropertiesTable(fSurfaceMPTGr);
	auto surfaceGr = new G4LogicalBorderSurface("SurfaceG", fTankGr, world_PV, fSurfaceGr);
	auto opticalSurfaceGr = dynamic_cast<G4OpticalSurface*>(surfaceGr->GetSurface(fTankGr, world_PV)->GetSurfaceProperty());

	fSurfaceG = new G4OpticalSurface("SurfaceG");
	fSurfaceG->SetType(dielectric_dielectric);
	fSurfaceG->SetFinish(ground);
	fSurfaceG->SetModel(unified);
	fSurfaceG->SetMaterialPropertiesTable(fSurfaceMPTG);
	auto surfaceG = new G4LogicalBorderSurface("SurfaceG", fTankG, world_PV, fSurfaceG);
	auto opticalSurfaceG = dynamic_cast<G4OpticalSurface*>(surfaceG->GetSurface(fTankG, world_PV)->GetSurfaceProperty());

	fSurfaceR = new G4OpticalSurface("SurfaceR");
	fSurfaceR->SetType(dielectric_metal);
	fSurfaceR->SetFinish(ground);
	fSurfaceR->SetModel(unified);
	fSurfaceR->SetMaterialPropertiesTable(fSurfaceMPTR);

	auto surfaceRingBoxZnS = new G4LogicalBorderSurface("SurfaceR", RingBox, world_PV, fSurfaceR);
	auto opticalSurfaceRingBoxZnS = dynamic_cast<G4OpticalSurface*>(surfaceRingBoxZnS->GetSurface(RingBox, world_PV)->GetSurfaceProperty());

	auto surfaceRPla = new G4LogicalBorderSurface("SurfaceR", fTankRPla, world_PV, fSurfaceR);
	auto opticalSurfaceRPla = dynamic_cast<G4OpticalSurface*>(surfaceRPla->GetSurface(fTankRPla, world_PV)->GetSurfaceProperty());

	auto surfaceRingBoxDET = new G4LogicalBorderSurface("SurfaceR", DETRingBox, world_PV, fSurfaceR);
	auto opticalSurfaceRingBoxDET = dynamic_cast<G4OpticalSurface*>(surfaceRingBoxDET->GetSurface(DETRingBox, world_PV)->GetSurfaceProperty());

	auto surfaceGSO16 = new G4LogicalBorderSurface("SurfaceR", GSO16, world_PV, fSurfaceR);
	auto opticalSurfaceGSO16 = dynamic_cast<G4OpticalSurface*>(surfaceGSO16->GetSurface(GSO16, world_PV)->GetSurfaceProperty());



	G4cout << "---------- opticalSurface->DumpInfo ----------" << G4endl;
	if (opticalSurface2) {
		G4cout << "----- ZnS -----" << G4endl;
		opticalSurface2->DumpInfo();
	}
	// if(opticalSurface3) {
	 //G4cout << "----- Plastic -----" << G4endl;
	 //opticalSurface3->DumpInfo();
  // }
	if (opticalSurface) {
		G4cout << "----- Detector -----" << G4endl;
		opticalSurface->DumpInfo();
	}

	G4cout << "------------------------------" << G4endl;

	if (fTankMaterial2->GetMaterialPropertiesTable()) {
		G4cout << "----- ZnS -----" << G4endl;
		fTankMaterial2->GetMaterialPropertiesTable()->DumpTable();
	}
	if (fTankMaterialPET->GetMaterialPropertiesTable()) {
		G4cout << "----- ZnS -----" << G4endl;
		fTankMaterialPET->GetMaterialPropertiesTable()->DumpTable();
	}
	if (fTankMaterial3->GetMaterialPropertiesTable()) {
		G4cout << "----- Plastic -----" << G4endl;
		fTankMaterial3->GetMaterialPropertiesTable()->DumpTable();
	}
	if (fTankMaterial->GetMaterialPropertiesTable()) {
		G4cout << "----- Detector -----" << G4endl;
		fTankMaterial->GetMaterialPropertiesTable()->DumpTable();
	}
	G4cout << "---------- end of propertisTable ----------\n" << G4endl;

	return world_PV;
}

void DetectorConstruction::SetSurfaceSigmaAlpha(G4double v)
{
	fSurface->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurface->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlpha2(G4double v)
{
	fSurface2->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurface2->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlphaPET(G4double v)
{
	fSurfacePET->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurfacePET->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlpha3(G4double v)
{
	fSurface3->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurface3->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlpha4(G4double v)
{
	fSurface4->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurface4->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlphaGr(G4double v)
{
	fSurfaceGr->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurfaceGr->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlphaG(G4double v)
{
	fSurfaceG->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurfaceG->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfaceSigmaAlphaR(G4double v)
{
	fSurfaceR->SetSigmaAlpha(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface sigma alpha set to: " << fSurfaceR->GetSigmaAlpha()
		<< G4endl;
}

void DetectorConstruction::SetSurfacePolish(G4double v)
{
	fSurface->SetPolish(v);
	G4RunManager::GetRunManager()->GeometryHasBeenModified();

	G4cout << "Surface polish set to: " << fSurface->GetPolish() << G4endl;
}

void DetectorConstruction::AddTankMPV(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPT->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT->DumpTable();
	G4cout << "............." << G4endl;
}

void DetectorConstruction::AddTankMPV2(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPT2->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT2->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPVPET(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPTPET->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTPET->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPV3(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPT3->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT3->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPV4(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPT4->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT4->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPVGr(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPTGr->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTGr->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPVG(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fTankMPTG->AddProperty(prop, mpv);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTG->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddReflectorMPV(const G4String& prop, G4MaterialPropertyVector* mpv) {
	if (!fReflectorMPT) {
		fReflectorMPT = new G4MaterialPropertiesTable();
	}
	fReflectorMPT->AddProperty(prop, mpv);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddWorldMPV(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fWorldMPT->AddProperty(prop, mpv);
	G4cout << "The MPT for the world is now: " << G4endl;
	fWorldMPT->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPV(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPT->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPV2(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPT2->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT2->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPVPET(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPTPET->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPTPET->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPV3(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPT3->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT3->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPV4(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPT4->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT4->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPVGr(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPTGr->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPTGr->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPVG(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPTG->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPTG->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPVR(const G4String& prop,
	G4MaterialPropertyVector* mpv)
{
	fSurfaceMPTR->AddProperty(prop, mpv);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPTR->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPC(const G4String& prop, G4double v)
{
	fTankMPT->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPC2(const G4String& prop, G4double v)
{
	fTankMPT2->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT2->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPCPET(const G4String& prop, G4double v)
{
	fTankMPTPET->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTPET->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPC3(const G4String& prop, G4double v)
{
	fTankMPT3->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT3->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPC4(const G4String& prop, G4double v)
{
	fTankMPT4->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPT4->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPCGr(const G4String& prop, G4double v)
{
	fTankMPTGr->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTGr->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddTankMPCG(const G4String& prop, G4double v)
{
	fTankMPTG->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fTankMPTG->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddReflectorMPC(const G4String& prop, G4double v)
{
	fReflectorMPT->AddConstProperty(prop, v);
	G4cout << "The MPT for the box is now: " << G4endl;
	fReflectorMPT->DumpTable();
	G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddWorldMPC(const G4String& prop, G4double v)
{
	fWorldMPT->AddConstProperty(prop, v);
	G4cout << "The MPT for the world is now: " << G4endl;
	fWorldMPT->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPC(const G4String& prop, G4double v)
{
	fSurfaceMPT->AddConstProperty(prop, v);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPC2(const G4String& prop, G4double v)
{
	fSurfaceMPT2->AddConstProperty(prop, v);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT2->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPC3(const G4String& prop, G4double v)
{
	fSurfaceMPT3->AddConstProperty(prop, v);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT3->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPC4(const G4String& prop, G4double v)
{
	fSurfaceMPT4->AddConstProperty(prop, v);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPT4->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPCG(const G4String& prop, G4double v)
{
	fSurfaceMPTG->AddConstProperty(prop, v);
	G4cout << "The MPT for the surface is now: " << G4endl;
	fSurfaceMPTG->DumpTable();
	G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetWorldMaterial(const G4String& mat)
{
	G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
	if (pmat && fWorldMaterial != pmat)
	{
		fWorldMaterial = pmat;
		if (fWorld_LV)
		{
			fWorld_LV->SetMaterial(fWorldMaterial);
			fWorldMaterial->SetMaterialPropertiesTable(fWorldMPT);
		}
		G4RunManager::GetRunManager()->PhysicsHasBeenModified();
		G4cout << "World material set to " << fWorldMaterial->GetName() << G4endl;
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetTankMaterial(const G4String& mat)
{
	G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
	//  if(pmat && fTankMaterial != pmat)
	//  {
	fTankMaterial = pmat;
	if (fTank_LV)
	{
		fTank_LV->SetMaterial(fTankMaterial);
		fTankMaterial->SetMaterialPropertiesTable(fTankMPT);
		fTankMaterial->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
	}
	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4cout << "Tank material set to " << fTankMaterial->GetName() << G4endl;
	//  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetTankMaterial2(const G4String& mat)
{
	G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
	fTankMaterial2 = pmat;
	if (fTank2_LV)
	{
		fTank2_LV->SetMaterial(fTankMaterial2);
		fTankMaterial2->SetMaterialPropertiesTable(fTankMPT2);
		//fTankMaterial2->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
	}
	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4cout << "Tank material set to " << fTankMaterial2->GetName() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetTankMaterialPET(const G4String& mat)
{
	G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
	fTankMaterialPET = pmat;
	if (fTankPET_LV)
	{
		fTankPET_LV->SetMaterial(fTankMaterialPET);
		fTankMaterialPET->SetMaterialPropertiesTable(fTankMPTPET);
		//fTankMaterial2->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
	}
	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4cout << "Tank material set to " << fTankMaterialPET->GetName() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetTankMaterial3(const G4String&)
{
	if (fTank3_LV)
	{
		fTank3_LV->SetMaterial(fTankMaterial3);
		fTankMaterial3->SetMaterialPropertiesTable(fTankMPT3);
		//fTankMaterial3->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);
	}
	G4RunManager::GetRunManager()->PhysicsHasBeenModified();
	G4cout << "Tank material set to " << fTankMaterial3->GetName() << G4endl;
}


G4OpticalSurface* DetectorConstruction::GetTankOpticalSurface() const {
	return fSurface;
}

G4OpticalSurface* DetectorConstruction::GetTankOpticalSurface2() const {
	return fSurface2;
}

G4OpticalSurface* DetectorConstruction::GetTankOpticalSurfacePET() const {
	return fSurfacePET;
}

G4OpticalSurface* DetectorConstruction::GetTankOpticalSurface3() const {
	return fSurface3;
}

G4OpticalSurface* DetectorConstruction::GetTankOpticalSurfaceR() const {
	return fSurfaceR;
}

G4OpticalSurface* DetectorConstruction::GetZnSPlasticOpticalSurfaceMPT() const {
	return SurfaceZnSPlastic;
}

G4MaterialPropertiesTable* DetectorConstruction::GetZnSPlasticSurface() const {
	return SurfaceZnSPlastic->GetMaterialPropertiesTable();
}

G4OpticalSurface* DetectorConstruction::GetRefPlaOpticalSurfaceMPT() const {
	return SurfaceRefPla;
}

G4MaterialPropertiesTable* DetectorConstruction::GetRefPlaSurface() const {
	return SurfaceRefPla->GetMaterialPropertiesTable();
}


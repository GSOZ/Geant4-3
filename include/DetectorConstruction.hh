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
/// \file optical/OpNovice2/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4OpticalSurface.hh"
#include "G4RunManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnionSolid.hh"

#include <CLHEP/Units/SystemOfUnits.h>

class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction() override;

	G4VPhysicalVolume* Construct() override;

	G4VPhysicalVolume* GetTank() { return fTank; }
	G4double GetTankXSize() { return fTank_x; }

	G4OpticalSurface* GetTankOpticalSurface() const;
	G4OpticalSurface* GetTankOpticalSurface2() const;
	G4OpticalSurface* GetTankOpticalSurfacePET() const;
	G4OpticalSurface* GetTankOpticalSurface3() const;
	G4OpticalSurface* GetTankOpticalSurfaceR() const;
	G4OpticalSurface* GetZnSPlasticOpticalSurfaceMPT() const;
	G4OpticalSurface* GetRefPlaOpticalSurfaceMPT() const;
	G4OpticalSurface* GetSurface(void) { return fSurface; }
	G4OpticalSurface* GetOpticalSurface(const G4String& name) const;

	G4MaterialPropertiesTable* GetSurfaceMPT() const { return fSurfaceMPT; }
	G4MaterialPropertiesTable* GetSurfaceMPT2() const { return fSurfaceMPT2; }
	G4MaterialPropertiesTable* GetSurfaceMPTPET() const { return fSurfaceMPTPET; }
	G4MaterialPropertiesTable* GetSurfaceMPT3() const { return fSurfaceMPT3; }
	G4MaterialPropertiesTable* GetReflectorMPT() const { return fSurfaceMPTR; }

	G4MaterialPropertiesTable* GetZnSPlasticSurface() const;
	G4MaterialPropertiesTable* GetRefPlaSurface() const;

	void SetSurfaceFinish(const G4OpticalSurfaceFinish finish)
	{
		fSurface->SetFinish(finish);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}

	void SetSurfaceFinish2(const G4OpticalSurfaceFinish finish)
	{
		fSurface2->SetFinish(finish);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}

	void SetSurfaceFinishPET(const G4OpticalSurfaceFinish finish)
	{
		fSurfacePET->SetFinish(finish);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}

	void SetSurfaceFinish3(const G4OpticalSurfaceFinish finish)
	{
		fSurface3->SetFinish(finish);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}



	G4OpticalSurfaceFinish GetSurfaceFinish()
	{
		return fSurface->GetFinish();
	}

	void SetSurfaceType(const G4SurfaceType type)
	{
		fSurface->SetType(type);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}

	void SetSurfaceModel(const G4OpticalSurfaceModel model)
	{
		fSurface->SetModel(model);
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}
	G4OpticalSurfaceModel GetSurfaceModel() { return fSurface->GetModel(); }

	void SetSurfaceSigmaAlpha(G4double v);
	void SetSurfaceSigmaAlpha2(G4double v);
	void SetSurfaceSigmaAlphaPET(G4double v);
	void SetSurfaceSigmaAlpha3(G4double v);
	void SetSurfaceSigmaAlpha4(G4double v);
	void SetSurfaceSigmaAlphaGr(G4double v);
	void SetSurfaceSigmaAlphaG(G4double v);
	void SetSurfaceSigmaAlphaR(G4double v);
	void SetSurfacePolish(G4double v);

	void AddTankMPV(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPC(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetTankMaterialPropertiesTable()
	{
		return fTankMPT;
	}

	void AddTankMPV2(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPC2(const G4String& prop, G4double v);

	void AddTankMPVPET(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPCPET(const G4String& prop, G4double v);

	void AddTankMPV3(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPC3(const G4String& prop, G4double v);

	void AddTankMPV4(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPC4(const G4String& prop, G4double v);

	void AddTankMPVGr(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPCGr(const G4String& prop, G4double v);

	void AddTankMPVG(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddTankMPCG(const G4String& prop, G4double v);



	void AddReflectorMPV(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddReflectorMPC(const G4String& prop, G4double v);

	void AddWorldMPV(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddWorldMPC(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetWorldMaterialPropertiesTable()
	{
		return fWorldMPT;
	}

	void AddSurfaceMPV(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPC(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTable()
	{
		return fSurfaceMPT;
	}

	void AddSurfaceMPV2(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPC2(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTable2()
	{
		return fSurfaceMPT2;
	}

	void AddSurfaceMPVPET(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPCPET(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTablePET()
	{
		return fSurfaceMPTPET;
	}

	void AddSurfaceMPV3(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPC3(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTable3()
	{
		return fSurfaceMPT3;
	}

	void AddSurfaceMPV4(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPC4(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTable4()
	{
		return fSurfaceMPT4;
	}

	void AddSurfaceMPVGr(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPCGr(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTableGr()
	{
		return fSurfaceMPTGr;
	}

	void AddSurfaceMPVG(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPCG(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTableG()
	{
		return fSurfaceMPTG;
	}

	void AddSurfaceMPVR(const G4String& prop, G4MaterialPropertyVector* mpv);
	void AddSurfaceMPCR(const G4String& prop, G4double v);
	G4MaterialPropertiesTable* GetSurfaceMaterialPropertiesTableR()
	{
		return fSurfaceMPTR;
	}



	void SetWorldMaterial(const G4String&);
	void SetTankMaterial(const G4String&);
	void SetTankMaterial2(const G4String&);
	void SetTankMaterialPET(const G4String&);
	void SetTankMaterial3(const G4String&);
	void SetTankMaterial4(const G4String&);
	void SetTankMaterialGr(const G4String&);
	void SetTankMaterialG(const G4String&);
	void SetTankMaterialR(const G4String&);

	G4Material* GetWorldMaterial() const { return fWorldMaterial; }
	G4Material* GetTankMaterial() const { return fTankMaterial; }
	G4Material* GetTankMaterial2() const { return fTankMaterial2; }
	G4Material* GetTankMaterial3() const { return fTankMaterial3; }
	G4Material* GetTankMaterial4() const { return fTankMaterial3; }
	G4Material* GetTankMaterialGr() const { return fTankMaterialGr; }
	G4Material* GetTankMaterialG() const { return fTankMaterialG; }
	G4Material* GetTankMaterialR() const { return fTankMaterialR; }

private:
	G4double fExpHall_x = 0.5 * CLHEP::m;
	G4double fExpHall_y = 0.5 * CLHEP::m;
	G4double fExpHall_z = 0.5 * CLHEP::m;

	G4VPhysicalVolume* fTank = nullptr;
	G4VPhysicalVolume* fTank2 = nullptr;
	G4VPhysicalVolume* fTankPET = nullptr;
	G4VPhysicalVolume* fTank3 = nullptr;
	G4VPhysicalVolume* GreaseGSO_x1 = nullptr;
	G4VPhysicalVolume* GreaseGSO_x2 = nullptr;
	G4VPhysicalVolume* GreaseGSO_x3 = nullptr;
	G4VPhysicalVolume* GreaseGSO_x4 = nullptr;
	G4VPhysicalVolume* GreaseGSO_x5 = nullptr;
	G4VPhysicalVolume* GreaseGSO_y1 = nullptr;
	G4VPhysicalVolume* GreaseGSO_y2 = nullptr;
	G4VPhysicalVolume* GreaseGSO_y3 = nullptr;
	G4VPhysicalVolume* GreaseGSO_y4 = nullptr;
	G4VPhysicalVolume* GreaseGSO_y5 = nullptr;
	G4VPhysicalVolume* GreasePETPla = nullptr;
	G4VPhysicalVolume* GreasePlaGSO = nullptr;
	G4VPhysicalVolume* GSO16 = nullptr;
	G4VPhysicalVolume* GreaseGSOGuide = nullptr;
	G4VPhysicalVolume* GreaseGuideDET = nullptr;
	G4VPhysicalVolume* fTankGr = nullptr;
	G4VPhysicalVolume* fTankG = nullptr;
	G4VPhysicalVolume* fTank4a = nullptr;
	G4VPhysicalVolume* RingBox = nullptr;
	G4VPhysicalVolume* GSORingBox = nullptr;
	G4VPhysicalVolume* fTankRPla = nullptr;
	G4VPhysicalVolume* DETRingBox = nullptr;

	G4UnionSolid* GreaseGridUnion = nullptr;


	//Size control
	//Detector
	G4double fTank_x = 2.5 * CLHEP::mm;
	G4double fTank_y = 2.5 * CLHEP::mm;
	G4double fTank_z = 1.0 * CLHEP::mm;

	//ZnS
	G4double fTank2_x = 5.00 * CLHEP::mm;
	G4double fTank2_y = 5.00 * CLHEP::mm;
	G4double fTank2_z = 0.004 * CLHEP::mm;

	//ZnS_PET
	G4double fTankPET_x = fTank2_x * CLHEP::mm;
	G4double fTankPET_y = fTank2_y * CLHEP::mm;
	G4double fTankPET_z = 0.121 * CLHEP::mm;

	//ZnS_Reflector_Out
	G4double fTankRZnSout_x = fTank2_x + 0.01 * CLHEP::mm;
	G4double fTankRZnSout_y = fTank2_y + 0.01 * CLHEP::mm;
	G4double fTankRZnSout_z = 0.005 * CLHEP::mm;

	//ZnS_Reflector_In
	G4double fTankRZnSin_x = fTank2_x + 0.01 * CLHEP::mm;
	G4double fTankRZnSin_y = fTank2_y + 0.01 * CLHEP::mm;
	G4double fTankRZnSin_z = fTankRZnSout_z - 0.005 * CLHEP::mm;

	//Plastic
	G4double fTank3_x = fTank2_y * CLHEP::mm;
	G4double fTank3_y = fTank2_y * CLHEP::mm;
	G4double fTank3_z = 7.5 * CLHEP::mm;

	//Greese
	G4double Greese_z = 0.005 * CLHEP::mm;

	//GSO
	G4double fTank4_x = 1.25 * CLHEP::mm;
	G4double fTank4_y = 1.25 * CLHEP::mm;
	G4double fTank4_z = 12.5 * CLHEP::mm;
	G4double fTank4_zGrid = 12.55 * CLHEP::mm;

	G4double fTank4_xGap = fTank4_x + 0.002 * CLHEP::mm;
	G4double fTank4_yGap = fTank4_y + 0.002 * CLHEP::mm;
	G4double fTank4_xGap2 = fTank4_x + 0.00375 * CLHEP::mm;
	G4double fTank4_yGap2 = fTank4_y + 0.00342625 * CLHEP::mm;

	//GreeseGrid
	G4double GreeseGrid_x = (fTank4_xGap * 4) - 0.002 * CLHEP::mm;
	G4double GreeseGrid_y = 0.002 * CLHEP::mm;

	// Reflector_Detector
	G4double fTankG_x = 5.01 * CLHEP::mm;
	G4double fTankG_y = 5.01 * CLHEP::mm;
	G4double fTankG_z = 0.5 * CLHEP::mm;

	//GSO_Reflector_Out
	G4double fTankRGSOout_x = fTank2_x + 0.2 * CLHEP::mm;
	G4double fTankRGSOout_y = fTank2_y + 0.2 * CLHEP::mm;
	G4double fTankRGSOout_z = fTankRZnSout_z + fTank2_z + fTankPET_z + fTank3_z + fTank4_z + Greese_z + Greese_z + Greese_z;

	//GSO_Reflector_In
	G4double fTankRGSOin_x = fTank2_x + 0.01 * CLHEP::mm;
	G4double fTankRGSOin_y = fTank2_y + 0.01 * CLHEP::mm;
	G4double fTankRGSOin_z = fTankRZnSout_z + fTank2_z + fTankPET_z + fTank3_z + fTank4_z + Greese_z + Greese_z + Greese_z + 0.01 * CLHEP::mm;

	//Detector_Reflector_Out
	G4double fTankRDETout_x = fTank_x + 0.2 * CLHEP::mm;
	G4double fTankRDETout_y = fTank_y + 0.2 * CLHEP::mm;
	G4double fTankRDETout_z = fTank_z;

	//Detector_Reflector_In
	G4double fTankRDETin_x = fTank_x * CLHEP::mm;
	G4double fTankRDETin_y = fTank_y * CLHEP::mm;
	G4double fTankRDETin_z = fTank_z + 0.01 * CLHEP::mm;

	G4LogicalVolume* fWorld_LV = nullptr;
	G4LogicalVolume* fTank_LV = nullptr;
	G4LogicalVolume* fTank2_LV = nullptr;
	G4LogicalVolume* fTankPET_LV = nullptr;
	G4LogicalVolume* fTank3_LV = nullptr;
	G4LogicalVolume* Grease_LV = nullptr;
	G4LogicalVolume* Grease_LV2 = nullptr;
	G4LogicalVolume* Grease_LV3 = nullptr;
	G4LogicalVolume* GreaseGSOx_LV = nullptr;
	G4LogicalVolume* GreaseGSOy_LV = nullptr;
	G4LogicalVolume* GreaseGSOxy_LV = nullptr;
	G4LogicalVolume* GSO16_LV = nullptr;
	G4LogicalVolume* fTankG_LV = nullptr;
	G4LogicalVolume* fTank4_LV = nullptr;
	G4LogicalVolume* RingBox_LV = nullptr;
	G4LogicalVolume* GSORingBox_LV = nullptr;
	G4LogicalVolume* reflector_LV = nullptr;
	G4LogicalVolume* DETRingBox_LV = nullptr;

	G4Material* fWorldMaterial = nullptr;
	G4Material* fTankMaterial = nullptr;
	G4Material* fTankMaterial2 = nullptr;
	G4Material* fTankMaterialPET = nullptr;
	G4Material* fTankMaterial3 = nullptr;
	G4Material* fTankMaterial4 = nullptr;
	G4Material* fTankMaterialGr = nullptr;
	G4Material* fTankMaterialG = nullptr;
	G4Material* fTankMaterialR = nullptr;

	G4OpticalSurface* fSurface = nullptr;
	G4OpticalSurface* fSurface2 = nullptr;
	G4OpticalSurface* fSurfacePET = nullptr;
	G4OpticalSurface* fSurface3 = nullptr;
	G4OpticalSurface* fSurface4 = nullptr;
	G4OpticalSurface* fSurfaceGr = nullptr;
	G4OpticalSurface* fSurfaceG = nullptr;
	G4OpticalSurface* fSurfaceR = nullptr;
	G4OpticalSurface* SurfaceZnSPlastic = nullptr;
	G4OpticalSurface* SurfaceRefPla = nullptr;

	G4MaterialPropertiesTable* fTankMPT = nullptr;
	G4MaterialPropertiesTable* fTankMPT2 = nullptr;
	G4MaterialPropertiesTable* fTankMPTPET = nullptr;
	G4MaterialPropertiesTable* fTankMPT3 = nullptr;
	G4MaterialPropertiesTable* fTankMPT4 = nullptr;
	G4MaterialPropertiesTable* fTankMPTGr = nullptr;
	G4MaterialPropertiesTable* fTankMPTG = nullptr;
	G4MaterialPropertiesTable* fReflectorMPT = nullptr;
	G4MaterialPropertiesTable* fWorldMPT = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPT = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPT2 = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPTPET = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPT3 = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPT4 = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPTGr = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPTG = nullptr;
	G4MaterialPropertiesTable* fSurfaceMPTR = nullptr;

	DetectorMessenger* fDetectorMessenger = nullptr;
};

#endif /*DetectorConstruction_h*/

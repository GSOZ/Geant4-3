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
//
/// \file optical/OpNovice2/include/ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

class DetectorConstruction;
class PrimaryGeneratorAction;  // �ǉ��F�v���C�}��������N���X�̑O���錾

#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
	ActionInitialization(DetectorConstruction* detector, const G4String& outputFileName);
	~ActionInitialization() override = default;

	void SetOutputFileName(const G4String& fname);
	void BuildForMaster() const override;
	void Build() const override;

	void SetPrimaryGenerator(PrimaryGeneratorAction* pg);
	PrimaryGeneratorAction* GetPrimaryGenerator() const;

private:
	DetectorConstruction* fDetector;
	G4String fOutputFileName; // �o�̓t�@�C������ێ�

	mutable PrimaryGeneratorAction* fPrimaryGenerator = nullptr;    // --- PrimaryGeneratorAction�̃|�C���^��ێ����郁���o�ϐ� ---
};

#endif

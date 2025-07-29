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
/// \file optical/OpNovice2/src/Run.cc
/// \brief Implementation of the Run class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Run.hh"
#include "DetectorConstruction.hh"
#include "HistoManager.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <iomanip>
#include <numeric>
#include <fstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Run::Run()

	: G4Run(), fPhotonCount(0), fPhotonCountZnSaWorld(0), fPhotonCountZnSPlastic(0), fPhotonCountPlasticZnS(0), outputFileName("default_output.txt")
{
	fBoundaryProcs.assign(43, 0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::AddPhotonCount()
{
	fPhotonCount++;
	//std::cout << fPhotonCount << std::endl;
}

void Run::AddPhotonCountZW()
{
	fPhotonCountZnSaWorld++;
}

void Run::AddPhotonCountZP()
{
	fPhotonCountZnSPlastic++;
}

void Run::AddPhotonCountPZ()
{
	fPhotonCountPlasticZnS++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::ResetPhotonCount()
{
	fPhotonCount = 0;
	fPhotonCountZnSaWorld = 0;
	fPhotonCountZnSPlastic = 0;
	fPhotonCountPlasticZnS = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy,
	G4bool polarized, G4double polarization)
{
	fParticle = particle;
	fEkin = energy;
	fPolarized = polarized;
	fPolarization = polarization;
	//ResetPhotonCount();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::Merge(const G4Run* run)
{
	const Run* localRun = static_cast<const Run*>(run);

	// pass information about primary particle
	fParticle = localRun->fParticle;
	fEkin = localRun->fEkin;
	fPolarized = localRun->fPolarized;
	fPolarization = localRun->fPolarization;

	fCerenkovEnergy += localRun->fCerenkovEnergy;
	fScintEnergy += localRun->fScintEnergy;
	fWLSAbsorptionEnergy += localRun->fWLSAbsorptionEnergy;
	fWLSEmissionEnergy += localRun->fWLSEmissionEnergy;
	fWLS2AbsorptionEnergy += localRun->fWLS2AbsorptionEnergy;
	fWLS2EmissionEnergy += localRun->fWLS2EmissionEnergy;

	fCerenkovCount += localRun->fCerenkovCount;
	fScintCount += localRun->fScintCount;
	fWLSAbsorptionCount += localRun->fWLSAbsorptionCount;
	fWLSEmissionCount += localRun->fWLSEmissionCount;
	fWLS2AbsorptionCount += localRun->fWLS2AbsorptionCount;
	fWLS2EmissionCount += localRun->fWLS2EmissionCount;
	fRayleighCount += localRun->fRayleighCount;

	fTotalSurface += localRun->fTotalSurface;

	fOpAbsorption += localRun->fOpAbsorption;
	fOpAbsorptionPrior += localRun->fOpAbsorptionPrior;

	fPhotonCount += localRun->fPhotonCount;
	fPhotonCountZnSaWorld += localRun->fPhotonCountZnSaWorld;
	fPhotonCountZnSPlastic += localRun->fPhotonCountZnSPlastic;
	fPhotonCountPlasticZnS += localRun->fPhotonCountPlasticZnS;

	// 各スレッドで計測された α・β・γのカウントを統合
	fAlphaCount += localRun->fAlphaCount;
	fBetaCount += localRun->fBetaCount;
	fGammaCount += localRun->fGammaCount;

	for (size_t i = 0; i < fBoundaryProcs.size(); ++i)
	{
		fBoundaryProcs[i] += localRun->fBoundaryProcs[i];
	}

	G4Run::Merge(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void Run::EndOfRun()
{
	if (numberOfEvent == 0)
		return;

	if (outputFileName.empty())
	{
		G4cerr << "Output file name is not set!" << G4endl;
		return;
	}

	auto TotNbofEvents = (G4double)numberOfEvent;
	G4int detectedAlphas = GetAlphaCount();
	G4int betaCount = GetBetaCount();
	G4int gammaCount = GetGammaCount();


	if (numberOfEvent == 0) return;

	G4double createdPhotons = fScintCount / TotNbofEvents;
	G4double detectedPhotons = fPhotonCount;
	G4double photonYieldPercentage = 0.0;

	if (fScintCount != 0 && TotNbofEvents != 0) {
		photonYieldPercentage = (static_cast<G4double>(fPhotonCount) / createdPhotons) * 100;
	}

	G4cout << "-----------------------------------------------" << G4endl;
	G4cout << "particles: " << fParticle->GetParticleName() << " with energy " << G4BestUnit(fEkin, "Energy") << "." << G4endl;
	G4cout << "created photons : " << createdPhotons << G4endl;
	G4cout << "detected photons: " << detectedPhotons << G4endl;
	G4cout << "Final Alpha Count: " << fAlphaCount << G4endl;
	G4cout << "Final Beta Count: " << betaCount << G4endl;
	G4cout << "Final Gamma Count: " << gammaCount << G4endl;


	if (fScintCount != 0 && TotNbofEvents != 0) {
		photonYieldPercentage = (static_cast<G4double>(fPhotonCount) / (fScintCount / TotNbofEvents)) * 100;
	}
	G4cout << std::fixed << std::setprecision(2) << "detection yields: " << photonYieldPercentage << " %" << G4endl;
	G4cout << "-------------------------------------------------\n" << G4endl;

	std::ofstream outputFile(outputFileName, std::ios::app);

	if (!outputFile) {
		G4cerr << "Error opening file: " << outputFileName << G4endl;
		return;
	}

	outputFile << std::fixed << std::setprecision(2) << createdPhotons << " " << detectedPhotons << " " << photonYieldPercentage << " " << fAlphaCount << " " << betaCount << " " << gammaCount << std::endl;
	outputFile.close();
}

void Run::SetOutputFileName(const std::string& filename)
{
	if (filename.find(".txt") == std::string::npos) {
		outputFileName = filename + ".txt";
	}
	else {
		outputFileName = filename;
	}
}


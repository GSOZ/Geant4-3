#include "MyPMTSD.hh"
#include "G4SystemOfUnits.hh"

MyPMTSD::MyPMTSD(PMTWaveformSimulator* sim)
    : G4VSensitiveDetector("PMTSD"), fWaveSim(sim) {}

G4bool MyPMTSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    double arrivalTime = step->GetPreStepPoint()->GetGlobalTime() / ns;
    fWaveSim->AddPhoton(arrivalTime);
    return true;
}

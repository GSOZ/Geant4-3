#ifndef MY_PMT_SD_HH
#define MY_PMT_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "PMTWaveformSimulator.hh"

class MyPMTSD : public G4VSensitiveDetector {
public:
    explicit MyPMTSD(PMTWaveformSimulator* sim);
    ~MyPMTSD() override = default;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;

private:
    PMTWaveformSimulator* fWaveSim;
};

#endif // MY_PMT_SD_HH

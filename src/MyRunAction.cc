#include "MyRunAction.hh"
#include "G4Run.hh"

MyRunAction::MyRunAction(PMTWaveformSimulator* sim)
    : fWaveSim(sim) {}

void MyRunAction::EndOfRunAction(const G4Run*) {
    fWaveSim->SaveToFile("waveform.txt");
}

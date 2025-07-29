#ifndef MY_RUN_ACTION_HH
#define MY_RUN_ACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "PMTWaveformSimulator.hh"

class MyRunAction : public G4UserRunAction {
public:
    explicit MyRunAction(PMTWaveformSimulator* sim);
    ~MyRunAction() override = default;
    void BeginOfRunAction(const G4Run*) override {}
    void EndOfRunAction(const G4Run*) override;

private:
    PMTWaveformSimulator* fWaveSim;
};

#endif // MY_RUN_ACTION_HH

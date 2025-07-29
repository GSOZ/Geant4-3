#ifndef PMT_WAVEFORM_SIMULATOR_HH
#define PMT_WAVEFORM_SIMULATOR_HH

#include <vector>
#include <string>

class PMTWaveformSimulator {
public:
    PMTWaveformSimulator(double binWidth_ns, double totalTime_ns,
                         double rise_ns = 1.0, double fall_ns = 5.0,
                         double amplitude = 1.0);
    void AddPhoton(double arrivalTime_ns);
    void SaveToFile(const std::string& filename) const;

private:
    std::vector<double> timeBins;
    std::vector<double> signal;
    double binWidth;
    double riseTime;
    double fallTime;
    double pulseAmplitude;
};

#endif // PMT_WAVEFORM_SIMULATOR_HH

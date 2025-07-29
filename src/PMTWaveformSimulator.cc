#include "PMTWaveformSimulator.hh"
#include <cmath>
#include <fstream>

PMTWaveformSimulator::PMTWaveformSimulator(double binWidth_ns, double totalTime_ns,
                                           double rise_ns, double fall_ns,
                                           double amplitude)
    : binWidth(binWidth_ns), riseTime(rise_ns), fallTime(fall_ns), pulseAmplitude(amplitude)
{
    int binCount = static_cast<int>(totalTime_ns / binWidth);
    timeBins.resize(binCount);
    signal.assign(binCount, 0.0);
    for (int i = 0; i < binCount; ++i) {
        timeBins[i] = i * binWidth;
    }
}

void PMTWaveformSimulator::AddPhoton(double arrivalTime_ns) {
    for (size_t i = 0; i < timeBins.size(); ++i) {
        double t = timeBins[i] - arrivalTime_ns;
        if (t >= 0) {
            signal[i] += pulseAmplitude * std::exp(-t / fallTime) * (1 - std::exp(-t / riseTime));
        }
    }
}

void PMTWaveformSimulator::SaveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    for (size_t i = 0; i < timeBins.size(); ++i) {
        out << timeBins[i] << "\t" << signal[i] << "\n";
    }
}

#ifndef WAVFILE_H
#define WAVFILE_H

#include <string>
#include <vector>

class WavFile
{
private:
    std::vector<short> samples;
    unsigned int sampleRate;
    unsigned short channels;
    unsigned short audioFormat;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    unsigned int dataSize;
    double duration;
    short getMaxSample() const;
    short getMinSample() const;
    short getPeakAmplitude() const;
    double getAverageAmplitude() const;

public:
    bool open(std::string filename);
    void printInfo() const;
    void amplify(double gain);
};

#endif
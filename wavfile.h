#ifndef WAVFILE_H
#define WAVFILE_H

#include <string>
#include <vector>

class WavFile
{
private:
    char riff[4];
    char wave[4];
    char fmt[4];
    char dataHeader[4];
   
   


    std::vector<short> samples;
    unsigned int chunkSize;
    unsigned int fmtSize;
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
    bool write(std::string filename);
    void printInfo() const;
    void amplify(double gain);
};

#endif
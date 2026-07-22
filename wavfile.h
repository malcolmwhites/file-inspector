#ifndef WAVFILE_H
#define WAVFILE_H

#include <string>

class WavFile
{
private:
    unsigned int sampleRate;
    unsigned short channels;
    unsigned short audioFormat;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    unsigned int dataSize;
    double duration;
public:
    bool open(std::string filename);
    void printInfo() const;
};

#endif
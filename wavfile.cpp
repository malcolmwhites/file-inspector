#include "wavfile.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <cstring>



using namespace std;

bool WavFile::open(string filename)
{
    ifstream file(filename, ios::binary);

    if(!file.is_open())
    {
        return false;
    }
    file.read(riff,4);
    file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
    file.read(wave, 4);
    char chunkId[4];
    while(file.read(chunkId, 4)){
        unsigned int currentChunkSize;
        file.read(reinterpret_cast<char*>(&currentChunkSize), sizeof(currentChunkSize));
        if(memcmp(chunkId, "fmt ", 4) == 0){
           file.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
           file.read(reinterpret_cast<char*>(&channels), sizeof(channels));
           file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
           file.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));
           file.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
           file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));
        }
        else if(memcmp(chunkId, "data", 4) == 0){
            dataSize = currentChunkSize;
            samples.resize(currentChunkSize/sizeof(short));
            file.read(reinterpret_cast<char*>(samples.data()), currentChunkSize);
            return true;
        }
        else{
            file.seekg(currentChunkSize, ios::cur);
        }
    }
    return false;
}

void WavFile::printInfo() const
{
    cout << "Audio Format: " << audioFormat << endl;
    cout << "Channels: " << channels << endl;
    cout << "Sample Rate: " << sampleRate << endl;
    cout << "Byte Rate: " << byteRate << endl;
    cout << "Block Align: " << blockAlign << endl;
    cout << "Bits Per Sample: " << bitsPerSample << endl;
    cout << "Data Size: " << dataSize << endl;
    cout << "Number of Samples: " << samples.size() << endl;

    for (int i = 0; i < 11 && i < samples.size(); i++)
    {
        cout << "Sample " << i << ": " << samples[i] << endl;
    }

    cout << "Max Sample: " << getMaxSample() << endl;
    cout << "Min Sample: " << getMinSample() << endl;
    cout << "Peak Amplitude: " << getPeakAmplitude() << endl;
    cout << "Average Amplitude: " << getAverageAmplitude() << endl;
}
short WavFile::getMaxSample() const
{
    int maxIndex = 0;

    for (int i = 0; i < samples.size(); i++)
    {
        if (samples[i] > samples[maxIndex])
        {
            maxIndex = i;
        }
    }

    return samples[maxIndex];
}
short WavFile::getMinSample() const
{
    int minIndex = 0;

    for (int i = 0; i < samples.size(); i++)
    {
        if (samples[i] < samples[minIndex])
        {
            minIndex = i;
        }
    }

    return samples[minIndex];
}
short WavFile::getPeakAmplitude() const
{
    if (abs(getMinSample()) > getMaxSample())
    {
        return abs(getMinSample());
    }

    return getMaxSample();
}
double WavFile::getAverageAmplitude() const
{
    long long total = 0;

    for (int i = 0; i < samples.size(); i++)
    {
        total += abs(samples[i]);
    }

    return static_cast<double>(total) / samples.size();
}




    

    






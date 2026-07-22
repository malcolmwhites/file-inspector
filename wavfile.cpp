#include "wavfile.h"
#include <fstream>
#include <iostream>

using namespace std;

bool WavFile::open(string filename)
{
    ifstream file(filename, ios::binary);

    if(!file.is_open())
    {
        return false;
    }
    char riff[4];
    file.read(riff,4);
    file.seekg(8);
    char wave[4];
    file.read(wave, 4);
    char chunk[4];
file.read(chunk,4);

int chunkSize;
file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));

file.seekg(chunkSize, ios::cur);

char nextChunk[4];
file.read(nextChunk,4);

int fmtSize;
file.read(reinterpret_cast<char*>(&fmtSize), sizeof(fmtSize));
file.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
file.read(reinterpret_cast<char*>(&channels), sizeof(channels));
file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
file.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));
file.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));
file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
duration = static_cast<double>(dataSize) / byteRate;


    return true;
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
    cout << "Duration: " << duration << " seconds";
}


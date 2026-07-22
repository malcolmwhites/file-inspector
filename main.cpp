#include "wavfile.h"
#include <iostream>

using namespace std;

int main()
{
    WavFile wav;

    if(wav.open("kick.wav"))
    {
        wav.printInfo();
    }
    else
    {
        cout << "Failed." << endl;
    }
}
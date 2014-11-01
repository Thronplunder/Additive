#include "SineWave.h"
#include "RtAudio.h"
#include "sound.h"
using namespace stk;
// This tick() function handles sample computation only. It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
Sound *sine = (Sound *) dataPointer;
register StkFloat *samples = (StkFloat *) outputBuffer;
for ( unsigned int i=0; i<nBufferFrames; i++ )
*samples++ = sine->tick();
return 0;
}
int main()
{
// Set the global sample rate before creating class instances.
    Sound klang;
    RtAudio dac;
    klang.play();
    char keyhit;
    int freq;
    float vol;
    klang.addSine(0.01, 1000);
    std::cout << "10 Töne hinzufügen. Erst Lautstärke in Amplitude, dann Frequenz" << std::endl;
    for(int i = 0; i < 10; i++){
        std::cin >> vol >> freq;
        klang.addSine(vol, freq);
    }
    std::cout << "\n Enter um zu beenden\n";
    std::cin.get();
// Shut down the output stream.
    klang.close();
}

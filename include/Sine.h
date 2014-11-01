#include "SineWave.h"
#include <cmath>
#include <math.h>
using namespace stk;
class Sine: public SineWave{
    StkFloat freq;
	StkFloat volume;
	StkFloat bark;
	bool isMasked;
	bool isUnderThreshold;
	StkFloat freqToBark();
	void testThreshold();
	int index; //index zur übersichtlichkeit und erreichbarkeit
public:
    //gibt an ob schon von testmasking markiert wurde
	bool wasMasked;
	//rechnet amplitude in dB um, nicht mehr nötig
	StkFloat volumeToDB();
	//rechnet dB in Amplitude um
	StkFloat DBToVolume(StkFloat vol);

    Sine(StkFloat vol, StkFloat freq, int index);
    //gibt Frequenz zurück
	StkFloat getFreq();
	//gibt Amplitude zurück
    StkFloat getVol();
    //gibt Lautstärke zurück
	StkFloat getDB();
	//gibt an, ob Ton erklingt
	bool getState();
	//gibt an, ob Ton maskiert wird
	bool getMasking();
	//ändert Maskierungsstatus
	void setMasking(bool masking);
	//ändert Lautstärle
	void changeVol(StkFloat vol);
	//ändert Frequenz
	void changeFreq(int freq);
	//gibt frequenz in Bark zurück
	StkFloat getBark();
	//gibt index zurück
	int getIndex();
};


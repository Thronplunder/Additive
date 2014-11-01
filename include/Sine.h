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
	int index; //index zur �bersichtlichkeit und erreichbarkeit
public:
    //gibt an ob schon von testmasking markiert wurde
	bool wasMasked;
	//rechnet amplitude in dB um, nicht mehr n�tig
	StkFloat volumeToDB();
	//rechnet dB in Amplitude um
	StkFloat DBToVolume(StkFloat vol);

    Sine(StkFloat vol, StkFloat freq, int index);
    //gibt Frequenz zur�ck
	StkFloat getFreq();
	//gibt Amplitude zur�ck
    StkFloat getVol();
    //gibt Lautst�rke zur�ck
	StkFloat getDB();
	//gibt an, ob Ton erklingt
	bool getState();
	//gibt an, ob Ton maskiert wird
	bool getMasking();
	//�ndert Maskierungsstatus
	void setMasking(bool masking);
	//�ndert Lautst�rle
	void changeVol(StkFloat vol);
	//�ndert Frequenz
	void changeFreq(int freq);
	//gibt frequenz in Bark zur�ck
	StkFloat getBark();
	//gibt index zur�ck
	int getIndex();
};


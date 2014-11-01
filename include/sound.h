#include <vector>
#include "Sine.h"
//#include "RtAudio.h"

using namespace std;


class Sound{

    //Liste aller Sinust�ne
    vector<Sine> Sines;
    //Anzahl der T�ne, nicht mehr so wichtig
	int numSines, index;
	//Sortiert die T�ne aufsteigend nach Frequenz, wird f�r Masking genutzt
	void sortSines(int length);
	//Stellt fest ob T�ne maskiert oder demaskiert werden und stellt diese entsprechend stumm
	void testMasking();
    //Werte f�r Echtzeitaudioausgabe, eventuell nicht alles notwendig
    RtAudio stream;
    RtAudio::StreamParameters parameters;
    unsigned int bufferFrames;
    RtAudioFormat format;
public:
    Sound();
    //F�gt einen Sinuston hinzu, Lautst�rkeangabe in Amplitude (0-1)
    void addSine(StkFloat vol, StkFloat freq);
    //gibt den n�chsten Wert des Klangs zur�ck
    StkFloat tick();
    //spielt den Klang als Stream ab
    void play();
    //Stoppt den Stream, weiterspielen m�glich
    void stop();
    //Schlie�t den Stream
    void close();
    //gibt die Liste der einzelnen T�ne zur�ck
	vector<Sine> getSines();
	//l�scht alle T�ne
	void clear();
	//�ndert die Frequenz eines Tons
	void changeVolByIndex(int index, StkFloat vol);
	//�ndert die Frequenz nach index
	void changeFreqByIndex(int index, int freq);
	//l�scht einen einzelnen Ton nach einem index, der durchgez�hlt wird
	void deleteSineByIndex(int index);
	//Gibt Liste der Frequenzen zur�ck
	vector<int> getFrequencies();
	//l�scht einen Ton nach Frequenz
	void deleteSineByFrequency(int freq);
	//�ndert die globale Lautst�rke
	void changeGlobalVol(float interval);
};


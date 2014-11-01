#include <vector>
#include "Sine.h"
//#include "RtAudio.h"

using namespace std;


class Sound{

    //Liste aller Sinustöne
    vector<Sine> Sines;
    //Anzahl der Töne, nicht mehr so wichtig
	int numSines, index;
	//Sortiert die Töne aufsteigend nach Frequenz, wird für Masking genutzt
	void sortSines(int length);
	//Stellt fest ob Töne maskiert oder demaskiert werden und stellt diese entsprechend stumm
	void testMasking();
    //Werte für Echtzeitaudioausgabe, eventuell nicht alles notwendig
    RtAudio stream;
    RtAudio::StreamParameters parameters;
    unsigned int bufferFrames;
    RtAudioFormat format;
public:
    Sound();
    //Fügt einen Sinuston hinzu, Lautstärkeangabe in Amplitude (0-1)
    void addSine(StkFloat vol, StkFloat freq);
    //gibt den nächsten Wert des Klangs zurück
    StkFloat tick();
    //spielt den Klang als Stream ab
    void play();
    //Stoppt den Stream, weiterspielen möglich
    void stop();
    //Schließt den Stream
    void close();
    //gibt die Liste der einzelnen Töne zurück
	vector<Sine> getSines();
	//löscht alle Töne
	void clear();
	//ändert die Frequenz eines Tons
	void changeVolByIndex(int index, StkFloat vol);
	//ändert die Frequenz nach index
	void changeFreqByIndex(int index, int freq);
	//löscht einen einzelnen Ton nach einem index, der durchgezählt wird
	void deleteSineByIndex(int index);
	//Gibt Liste der Frequenzen zurück
	vector<int> getFrequencies();
	//löscht einen Ton nach Frequenz
	void deleteSineByFrequency(int freq);
	//ändert die globale Lautstärke
	void changeGlobalVol(float interval);
};


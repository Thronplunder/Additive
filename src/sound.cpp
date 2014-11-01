 
#include "sound.h"

Sound::Sound(){
    //richtet Echtzeitaudio ein
    parameters.deviceId = stream.getDefaultOutputDevice();
    parameters.nChannels = 1;
    format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    bufferFrames = RT_BUFFER_SIZE;
	this->numSines = 0;
	this->index = 0;
};

void Sound::addSine(StkFloat vol, StkFloat freq){
	Sines.push_back(Sine(vol, freq, this->index));
	this->numSines++;
	this->index++;
	sortSines(this->numSines);
	testMasking();
};


StkFloat Sound::tick(){
    StkFloat val = 0;
    int i;
    for (i = 0; i < Sines.size(); ++i){
        if(Sines[i].getState()){
            val += Sines[i].tick() * Sines[i].getVol();
        }
    };
	return val;
};


vector<Sine> Sound::getSines(){
	return Sines;
}

void Sound::clear(){
	this->Sines.clear();
}

void Sound::changeVolByIndex(int index, StkFloat vol){
			this->Sines.at(index).changeVol(vol);
			testMasking();
}


void Sound::changeFreqByIndex(int index, int freq){
	this->Sines.at(index).changeFreq(freq);
	testMasking();
}


void Sound::sortSines(int length){
	for (int i = 0; i < length -1; i++){
		if(this->Sines.at(i).getFreq() > this->Sines.at(i+1).getFreq()) swap(this->Sines.at(i), this->Sines.at(i+1));
	}
	if(length > 2) sortSines( length -1);
	else return;
}


void Sound::testMasking(){//testet alle Töne, ob sie maskiert werden oder nicht und setzt entsprechend einen bool-wert
    if(this->numSines == 1) this->Sines.at(0).setMasking(false);//workaround, falls nurnoch ein Ton gespielt wird
	float maskingThreshold = 1;
	for(int i = 0; i < this->numSines; i++){//Töne wurden diesen Durchlauf noch nicht maskiert
		this->Sines.at(i).wasMasked = false;
	}
	for(int i = 0; i < this->numSines; i++){
		if (this->Sines.at(i).getMasking() == false && this->Sines.at(i).getDB() > 10.0f){//prüfe nur ob maskiert wird, falls ton nicht selbst maskiert wird und ton lauter als 10db
			for(int j = i -1; j >= 0 && maskingThreshold > 0 ; j--){//linke Seite nach maskierten Teiltönen prüfen
				maskingThreshold = (this->Sines.at(i).getDB() - 10.0f) - (this->Sines.at(i).getBark() - this->Sines.at(j).getBark()) * 27.0f;//berechnung des Masking Thresholds an der Stelle des nächsten  Tones
				if(this->Sines.at(j).getDB() < maskingThreshold){// Falls der Ton leiser als der Threshold ist, ist er nicht hörbar
					this->Sines.at(j).setMasking(true);
					this->Sines.at(j).wasMasked = true;
				}
				else if(this->Sines.at(j).wasMasked == false){//Töne dürfen nicht demaskiert werden, falls sie schon maskiert wurden
					this->Sines.at(j).setMasking(false);
				}
			}
			maskingThreshold = 1; //Workaround um die Schleife durchlaufen zu lassen
			for(int j = i + 1; j < this->numSines && maskingThreshold > 0; j++){//funktioniert anscheinend, funktionisweise siehe oben
				maskingThreshold = (this->Sines.at(i).getDB() - 10) - (this->Sines.at(j).getBark() - this->Sines.at(i).getBark()) * 15.0f;
				if(this->Sines.at(j).getDB() < maskingThreshold){
					this->Sines.at(j).setMasking(true);
					this->Sines.at(j).wasMasked = true;
				}
				else if(this->Sines.at(j).wasMasked == false){
					this->Sines.at(j).setMasking(false);
				}
			}
		}
	}
}

//wird von play aufgerufen, wenn ein neues Buffer gefüllt werden muss. Funktioniert nicht so einfach als Memberfunktion
int tickbuffer(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
double streamTime, RtAudioStreamStatus status, void *dataPointer){
    Sound *klang = (Sound *) dataPointer;
    StkFloat *samples = (StkFloat *) outputBuffer;
     for ( unsigned int i=0; i<nBufferFrames; i++ ){
            *samples++ = klang->tick();
     }
     return 0;
};

void Sound::play(){
    stream.openStream(&parameters, NULL, format, (unsigned int) Stk::sampleRate(), &bufferFrames, &tickbuffer, this);
    stream.startStream();
};

void Sound::deleteSineByIndex(int index){
	this->Sines.erase(this->Sines.begin() + index);
	this->numSines--;
	testMasking();
}

vector<int> Sound::getFrequencies(){
    vector<int> frequencies;
    for(int i = 0; i < this->numSines; i++){
        frequencies.push_back(this->Sines.at(i).getFreq());
    }
    return frequencies;
}

void Sound::deleteSineByFrequency(int freq){
    for(int i = 0; i < this->numSines; i++){
        if(this->Sines.at(i).getFreq() == freq){
            this->Sines.erase(Sines.begin() + i);
            this->numSines--;
            testMasking();
            return;
        }
    }
}

void Sound::changeGlobalVol(float interval){
	for(int i = 0; i < this->numSines; i++){
		this->Sines.at(i).changeVol(this->Sines.at(i).getVol() + interval);
	}
}

void Sound::close(){
    this->stream.closeStream();
}

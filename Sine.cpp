 
#include "Sine.h"

Sine::Sine(StkFloat vol, StkFloat freq, int index){
        this->volume = vol;
        this->freq = freq;
		setFrequency(freq);
		testThreshold();
		this->bark = freqToBark();
		this->isMasked = false;
    }


StkFloat Sine::getVol(){
	return this->volume;
}

StkFloat Sine::getFreq(){
	return freq;
}

StkFloat Sine::freqToBark(){
	if(this->freq < 500) return (StkFloat) this->freq/100;
	else {
		return 9 + 4 * (log(this->freq /1000.0f) / log(2.0f));
	}
}

StkFloat Sine::volumeToDB(){
	return (20 * log10( (this->volume) / 0.000001));
}

StkFloat Sine::DBToVolume(StkFloat vol){
	return pow(10.0, vol/20.0 -6.0);
}

void Sine::testThreshold(){
	if ((this->volumeToDB()) >= 3.64 * pow( (this->freq /1000.0f), -0.8) - 6.5 * pow(2.718281, -0.6 * pow(this->freq /1000.0f - 3.3, 2)) +  0.001 * pow(this->freq/1000.0f, 4)) this->isUnderThreshold = false;
	else this->isUnderThreshold = true;
}

bool Sine::getState(){
	if(this->isMasked || this->isUnderThreshold) return false;
	else return true;
}


void Sine::changeVol(StkFloat vol){
	this->volume = vol;
	testThreshold();
}

void Sine::changeFreq(int freq){
	this->freq = freq;
	setFrequency(freq);
	testThreshold();
	this->bark = freqToBark();
}

StkFloat Sine::getBark(){
	return this->bark;
}

bool Sine::getMasking(){
	return this->isMasked;
}

void Sine::setMasking(bool masking){
	this->isMasked = masking;
}

StkFloat Sine::getDB(){
	return this->volumeToDB();
}

int Sine::getIndex(){
	return this->index;
}

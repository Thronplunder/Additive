CC = g++
LIBS=-lstk -lpthread -lasound

DEPS = sound.h Sine.h



Additive: 
	g++ -o additive main.cpp sound.cpp Sine.cpp $(LIBS)

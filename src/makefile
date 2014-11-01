IDIR = ../include
CC = g++
CFLAGS= -I$(IDIR)
DEPS = 
ODIR= obj
LDIR = .../lib

LIBS=-lstk

_DEPS = sound.h Sine.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sound.o Sine.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c §(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

Additive: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
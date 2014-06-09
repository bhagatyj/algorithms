IDIR =../../lib/include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=./obj
LDIR =../../lib/archive/

LIBS=-lm -llutils

_DEPS = ../../lib/include/*.h ./*.h ../../lib/archive/*
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testMain.o sllTest.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(LUTILLIB): $(LUTILC) $(LUTILH)
	cd $(LUTILDIR); make;

$(ODIR)/%.o: %.c $(DEPS) $(LUTILLIB)
		$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -L$(LDIR) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


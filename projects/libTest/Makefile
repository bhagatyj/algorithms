IDIR =../../lib/include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=./obj
LDIR =../../lib/archive/
LIBDIR=../../lib

LIBS=-lm -llutils

_DEPS = ../../lib/include/*.h ./*.h ../../lib/archive/*
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testMain.o sllTest.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(LIBUTIL): $(LIBUTILC) $(LIBUTILH)
	cd $(LIBDIR); make;

$(ODIR)/%.o: %.c $(DEPS) $(LUTILLIB)
		$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
		gcc -o $@ $^ $(CFLAGS) -L$(LDIR) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


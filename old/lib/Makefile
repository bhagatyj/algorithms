CC=gcc
CFLAGS=-Wall -c
LIBLDFLAGS=-cvq
LIBLD=ar

archive: archive/liblutils.a

include lutils/Makefile.def

archive/liblutils.a: $(LUTIL_SRC)
	cd lutils; make ; cd ..; cp lutils/obj/liblutils.a archive/

.PHONY: clean
clean:
	cd lutils; make clean


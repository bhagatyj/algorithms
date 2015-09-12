RM=rm -rf

all: main
main: .lib/libring.a
	g++ main.cpp -lring -L./.lib -o main

.lib/libring.a: .lib/ring.o
	ar rcs ./.lib/libring.a ./.lib/ring.o

.lib/ring.o:
	mkdir ./.lib
	g++ -c ring.cpp -o ./.lib/ring.o

clean:
	$(RM) ring.o libring.a main
	$(RM) ./.lib 
#g++ -c ring.cpp -o ring.o
#ar rcs libring.a ring.o
#g++ main.cpp -lring -L.


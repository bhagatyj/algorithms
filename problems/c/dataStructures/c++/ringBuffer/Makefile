RM=rm -rf

all: main
main: .lib/libringBuffer.a
	g++ main.cpp -lringBuffer -L./.lib -o main

.lib/libringBuffer.a: .lib/ringBuffer.o
	ar rcs ./.lib/libringBuffer.a ./.lib/ringBuffer.o

.lib/ringBuffer.o:
	mkdir -p ./.lib
	g++ -c ringBuffer.cpp -o ./.lib/ringBuffer.o

clean:
	$(RM) ringBuffer.o libringBuffer.a main
	$(RM) ./.lib 


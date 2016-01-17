RM=rm -rf

all: main
main: .lib/liblogBuffer.a
	g++ main.cpp -llogBuffer -L./.lib -o main

.lib/liblogBuffer.a: .lib/logBuffer.o
	ar rcs ./.lib/liblogBuffer.a ./.lib/logBuffer.o

.lib/logBuffer.o:
	mkdir -p ./.lib
	g++ -c logBuffer.cpp -o ./.lib/logBuffer.o

clean:
	$(RM) logBuffer.o liblogBuffer.a main
	$(RM) ./.lib 


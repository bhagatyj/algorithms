g++ -c ring.cpp -o ring.o
ar rcs libring.a ring.o
g++ main.cpp -lring -L.


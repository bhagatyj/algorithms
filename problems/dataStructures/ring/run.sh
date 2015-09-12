g++ -c ring.cpp -o ring.o
ar rcs libring.a ring.o
gcc main.cpp -lring -L.


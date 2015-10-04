#include "ring.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define RINGSIZE 1024
int main(int argc, char **argv) {

    Example::RingBuffer *myRingBuffer = new Example::RingBuffer(RINGSIZE+1);
    ifstream myFile;
    string line;

    myFile.open("main.cpp");
    while ( getline(myFilem line) ) {
        if ( myRingBuffer.push( line, strlen(line) ) != 0 ) {
            break;
        }
    }

    while ( ( line = myRingBuffer.pop() ) != 0 ) {
        cout << line << endl;
    }

}

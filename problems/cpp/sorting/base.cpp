#include "base.h"
#include <stdlib.h>

using namespace std;

Sort::Sort( int size ) {
    unsigned i;

    __store = new int[size];
    if ( __store == NULL ) {
        cout << "Error allocating store" << endl;
        __size = 0;
        return;
    }
    __size = size;
    srand (time(NULL));
    for (i=0; i<size; i++) {
        __store[i] = rand();
    }
        
}

void 
Sort::print() {
    unsigned i;

    cout << endl;
    cout << __size << " elements" << endl;
    for (i=0; i<__size; i++) {
        cout << "Element:" << i << "\t : \t"<< __store[i] << endl;
    }
}

int
Sort::is_sorted() {
    unsigned i;

    for (i=1; i<__size; i++) {
        if ( __store[i-1] > __store[i] ) {
            return false;
        }
    }
    return true;
}

void
Sort::sortIt() {
    return;
}

void
Sort::swap(unsigned i, unsigned j) {
    assert(i<__size);
    assert(j<__size);
    int tmp = __store[i];
    __store[i] = __store[j];
    __store[j] = tmp;
}

Sort::~Sort() {
    __size = 0;
    delete[] __store;
}

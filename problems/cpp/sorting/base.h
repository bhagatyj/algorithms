#include <iostream>
#include <assert.h>

#ifndef __BASE_H__
#define __BASE_H__

#define DEFAULT_SIZE (1000000)

class Sort {
    protected:
        int *__store;
        int __size;
    public:
        Sort( int size=DEFAULT_SIZE );
        int is_sorted();
        void fillRandom();
        virtual void sortIt();
        void print();
        void swap(unsigned i, unsigned j);
        ~Sort();
};

#endif

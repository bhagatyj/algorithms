// Implement a class that can calculate the running average of a stream of input numbers 

#include <iostream>

using namespace std;

class RunAverage {

    protected:
        float _average;
        int _count;

    public:
        void addNum( int newNumber );
        float average( void );
        RunAverage(void);
};

RunAverage::RunAverage(void) {
    _average = 0;
    _count = 0;
}

void
RunAverage::addNum( int newNumber )
{
    _average = ((_average * _count) + (newNumber * 1.0) ) / (_count + 1) ;
    _count++;
}

float
RunAverage::average( void ) {
    return _average;
}


int main (int argc, char **argv) {
    RunAverage ra;
    ra.addNum(5);
    ra.addNum(5);
    ra.addNum(10);
    ra.addNum(10);
    cout << ra.average();
}

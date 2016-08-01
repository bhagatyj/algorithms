#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
using namespace std;

class Data {
protected:
    int value; 
    int source; // indicates the vector this was picked from.

public:
    Data( int v, int s ) : value(v), source(s) {};
    Data() : value(0), source(-1) {};
    bool operator < ( const Data & other ) const {
        return ( value > other.value );
    }
    int getValue() { return value; }
    int getSource() { return source; }
    void print() { cout << "v:" << value << " s:" << source << endl; }
};

void 
printDataVector( vector<Data> dataSet ) {
    for( Data &data : dataSet ) {
        data.print();
    }
}
        
void
mergeKLists( vector< vector<int> > numLists, vector<int> &output ) {

    vector<Data> dataSet;
    
    // Remove any empty list.
    for( vector< vector< int > >::iterator it = numLists.begin(); it != numLists.end(); it++ ) {
        if( not it->size() ) {
            numLists.erase( it );
        }
    }

    // Make a dataSet using the first elements in each list.
    for(int i=0; i<numLists.size(); i++) {
        dataSet.push_back( Data( numLists[i][0], i) ); 
        numLists[i].erase( numLists[i].begin() );
    }
    
    // Make the heap and order it.
    make_heap( dataSet.begin(), dataSet.end() );

    while( not dataSet.empty() ) {
        pop_heap( dataSet.begin(), dataSet.end() );
        Data d = dataSet.back();
        output.push_back( d.getValue() );
        int source = d.getSource();
        if ( numLists[source].size() ) {
            // There are more elements in the same list.
            // Push the next element into the heap
            Data nextNumber( numLists[source][0], source );
            numLists[source].erase( numLists[source].begin() );
            dataSet[ dataSet.size() - 1 ] = nextNumber;
    
            push_heap( dataSet.begin(), dataSet.end() );
        } else {
            // There are no more elements in the same list.
            // Reduce the Heap size;
            dataSet.pop_back();
        }
    }
}

void
printIntVector( vector<int> &numbers ) {
   for( int n : numbers ) {
       cout << n << "\t" ;
   }
   cout << endl;
}

void
printIntVectorVector( vector< vector<int> > &numLists ) {
    int count = 0;
    for( vector<int> numbers : numLists ) {
        cout << "List:" << count++ << " size:" << numbers.size() << endl;
        for( int n : numbers ) {
            cout << n << "\t" ;
        }
        cout << endl;
    }
    cout << endl;
}


int main( ) {
    vector< vector< int > > numLists;
    vector<int> output;

    for( int i=0; i<8; i++ ) {
        vector<int> numbers;
        int count = rand() % 8;
        for( int j=0; j<count; j++) {
            numbers.push_back( rand() % 256 );   
        }
        sort( numbers.begin(), numbers.end() );
        numLists.push_back( numbers );
    }
    printIntVectorVector( numLists );
    mergeKLists( numLists, output );
    printIntVector( output );
}

#include <random>
#include <iostream>

using namespace std;

void
printIntVector( vector<int> &numbers ) {
    for( vector<int>::iterator it=numbers.begin(); it!=numbers.end(); it++) {
        cout << *it << "  " ;
    }
    cout << endl;
}

bool comp( const int &n1, const int &n2 ) {
    if ( n1 < n2 ) {
        return true;
    } else {
        return false;
    }
}

vector<int> 
sortUsingHeapApi( vector<int> &numbers) {
    vector<int> output;

    make_heap( numbers.begin(), numbers.end(), comp );
    
    while( not numbers.empty() ) {
        pop_heap( numbers.begin(), numbers.end() );
        output.push_back( numbers.back() );
        numbers.pop_back();
    }

    return output;
}

int main() {
    vector<int> numbers;
    vector<int> sorted;

    for(int i=0; i<10; i++) {
        numbers.push_back( rand() % 2048 );
    }
    printIntVector(numbers);
    sorted = sortUsingHeapApi(numbers);
    printIntVector(sorted);
}
    

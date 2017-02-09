#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
vector<int>
parseInts( string input) {

    stringstream ss(input);
    string item;
    vector<int> numbers;

    while( getline( ss, item, ',' ) ) {
        numbers.push_back( stoi(item) );
    }
    return numbers;
}

int main() {
    vector<int> numbers = parseInts("1,2,3,4,5");
    for( int &x : numbers ) {
        cout << x << "\t";
    }
    cout << endl;
}

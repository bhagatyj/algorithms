#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector< vector< string> > 
groupAnagrams( vector<string> input ) {
    vector< vector<string> > output;
    map< string, vector<string> > sorter;
    
    for( vector<string>::iterator it=input.begin(); it != input.end(); it++ ) {
        string key( it->begin(), it->end() );
        sort( key.begin(), key.end() );
        if( sorter.find( key ) == sorter.end() ) {
            vector<string> newEntry;
            newEntry.push_back( *it );
            sorter[ key ] = newEntry;
        } else {
            sorter[ key ].push_back( *it );
        }
    }
    for( map<string, vector<string> >::iterator it = sorter.begin();
                        it != sorter.end(); it++ ) {
        output.push_back( it->second );
    }
    return output;
}

int main() {

    vector< string> input;
    int count = 0;
    input.push_back( "add" );
    input.push_back( "aba" );
    input.push_back( "arc" );
    input.push_back( "car" );
    input.push_back( "bab" );
    input.push_back( "dad" );
    vector< vector< string> > result = groupAnagrams( input );
    cout << "--------------" << endl;
    for( vector< vector< string> >::iterator it = result.begin();
            it != result.end(); it++ ) {
        cout << "Group: " << count++ << endl;
        for( vector<string>::iterator it2 = it->begin();
                it2 != it->end(); it2++ ) {
            cout << "\t\t" << *it2 << endl;
        }
        cout << "--------------" << endl;
    }

}

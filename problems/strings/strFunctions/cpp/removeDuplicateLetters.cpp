#include <iostream>
#include <map>
#include <string>

using namespace std;

string
removeDupes( string input ) {

    string output;
    map<char, int> charMap;

    for( char ch : input ) {
        if ( not charMap[ch] ) { output.push_back(ch); }
        charMap[ch]++;
    }
    return output;
}
        

int main() {

    cout << removeDupes("hhhhhh") << endl;
    cout << removeDupes("hellohello") << endl;
    cout << removeDupes("hellohowareyou") << endl;

}

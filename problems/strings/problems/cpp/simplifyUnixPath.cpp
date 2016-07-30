#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
void
split ( string input, char delim, vector<string> &tokens)
{
    stringstream ssInput(input);
    string item;

    while( getline( ssInput, item, delim ) ) {
        tokens.push_back( item );
    }
}

string
simplify( string input ) {

    vector<string> inTokens;
    vector<string> outTokens;
    string output("/");
    split(input, '/', inTokens);
    
    for( string token : inTokens ) {
        if( token.compare("..") == 0 ) {
            if( ! outTokens.empty() ) {
                outTokens.pop_back();
            }
            continue;
        }
        // skip
        if( token.compare(".") == 0 ) { continue; }
        if( token.compare("") == 0 ) { continue; }
        outTokens.push_back( token );
    }
    for ( string token : outTokens ) {
        output += token;
        output += "/";
    }
    return output.substr(0, output.length() - 1 );
}

int main() {
    cout << simplify("/user/byj/../byj") << endl;
    cout << simplify("/user/byj/projects/../../byj") << endl;
}

#include <iostream>
#include <map>
#include <string>


using namespace std;
map<char, int> stringMap;
map<char, int> alreadyPrinted;

void stringMapInit( string input ) {
    for (char& c : input) {
        map<char, int>::iterator it = stringMap.find(c);
        if ( it == stringMap.end() ) {
            stringMap.insert( pair<char, int>(c, 1) );
        } else {
            stringMap[c]++;
        }
    }
}    

void walkAndPrint( string input ) {
    string output;
    map<char, int>::iterator it;
    map<char, int>::iterator curr;
    char lowest;
    int size = input.size();
    int lastLowest = 0;

    for (int i=0; i<size; i++) {
        char c = input[i];
        if ( stringMap.empty() ) {
            cout << "Empty map" << endl;
            break;
        }

        if (alreadyPrinted.find(c) != alreadyPrinted.end()) {
            continue;
        }

        it = stringMap.begin();
        lowest = it->first;

        cout << "Char :: " << c << " Lowest : " << lowest << endl;


        if ( c <= lowest ) {
            cout << "Appending lowest" << c << endl;
            output.append(string(1, c));
            stringMap.erase(c);
            alreadyPrinted.insert(pair<char, int>(c, 0));
            lastLowest = i;
        } else {
            int j;
            // Before appending a last chance guy
            // Check if there is anyone who is more deserving.
            for (j=lastLowest; j<i; j++) {
                if (input[j] < c) {
                    cout << "Appending more deserved folks";
                    if (alreadyPrinted.find(input[j]) != alreadyPrinted.end()) {
                        continue;
                    }
                    output.append(string(1, input[j]));
                    stringMap.erase(input[j]);
                    alreadyPrinted.insert(pair<char, int>(input[j], 0));
                    lastLowest = i;
                }
            }
            stringMap[c]--;
            if (stringMap[c] == 0) {
                cout << "Appending last chance " << c << endl;
                output.append(string(1,c));
                stringMap.erase(c);
                alreadyPrinted.insert(pair<char, int>(c, 0));
            }
            
        }
    }
    cout << "Here is the ans..." << output << endl;
}

int main(int argc, char **argv) {
    string input = string("cbacdcbc"); // expect acdb
    stringMapInit(input);
    map<char, int>::iterator it = stringMap.begin();
    for ( ; it != stringMap.end() ; ++it ) {
        cout << it->first << " --> " << it->second << endl;
    }
    walkAndPrint(input);
    //cout << stringMap << endl;
}

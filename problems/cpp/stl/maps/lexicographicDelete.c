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

    for (char& c : input) {
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


        if ( c == lowest ) {
            cout << "Appending lowest" << c << endl;
            output.append(string(1, c));
            stringMap.erase(c);
            alreadyPrinted.insert(pair<char, int>(c, 0));
        } else {
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
    string input = string("adasddascfefwcsa");
    stringMapInit(input);
    map<char, int>::iterator it = stringMap.begin();
    for ( ; it != stringMap.end() ; ++it ) {
        cout << it->first << " --> " << it->second << endl;
    }
    walkAndPrint(input);
    //cout << stringMap << endl;
}

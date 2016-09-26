#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
map<int, string> phoneMap;

void init() {
    phoneMap[1] = string("abc");
    phoneMap[2] = string("def");
    phoneMap[3] = string("ghi");
    phoneMap[4] = string("jkl");
    phoneMap[5] = string("mno");
    phoneMap[6] = string("pqr");
    phoneMap[7] = string("stu");
    phoneMap[8] = string("vwx");
    phoneMap[9] = string("yz");
    phoneMap[0] = string("A");
}

void
getCombo( vector<string> words, 
          vector<string> &combos, 
          string combo ) {

    if( words.size() == 0 ) { 
        return; 
    }

    if( not words.empty() ) {
        string word = words.front(); 
        words.erase( words.begin() );

        for( char c : word ) {
            if( words.size() == 0 ) {
                combos.push_back( combo + c );
            } else {
                getCombo( words, combos, combo + c );
            }
        }
    } 
}

vector<string> letterCombinations(string digits) {
    vector<string> answer;

    vector<string> groups;
    for( char c : digits ) {
        int value = c - '0';
        groups.push_back( phoneMap[value] );
    }

    vector<string> combos;
    getCombo( groups, combos, "" );
    for( auto it = combos.begin(); it != combos.end(); it++ ) {
        cout << *it << endl;
    }
    return answer;
}

int main() {
    init();
    letterCombinations("125");
}

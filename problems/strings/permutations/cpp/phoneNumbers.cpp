#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
map<int, vector<char> > numMap;

void
getPermutations( vector<int> phoneNum, vector<string> &permutations,
                    string wordSoFar, int pos ) {

    if( pos == phoneNum.size() ) {
        permutations.push_back( wordSoFar );
        return;
    }

    int i = phoneNum[ pos ];
    vector<char> letters = numMap[i];
    for( vector<char>::iterator it = letters.begin(); it != letters.end(); it++ ) {
        // CRITICAL COMMENT
        // It is important to change the values inside the function call and 
        // not change the original variables so that there are no 
        // side-effects in the original program.
        getPermutations( phoneNum, permutations, wordSoFar + *it, pos+1 );
    }
}

int main() {
    vector<char> x;
    vector<int> phoneNum;
    vector<string> phoneWords;

    x.push_back('a');
    x.push_back('b');
    numMap[2] =  x ;
    x.clear();
    x.push_back('c');
    x.push_back('d');
    numMap[3] =  x ;
    
    phoneNum.push_back(2);
    phoneNum.push_back(3);

    getPermutations( phoneNum, phoneWords, "", 0 );

    for( auto it=phoneWords.begin(); it<phoneWords.end(); it++) {
        cout << *it << endl;
    }

}

// USACO 2025 US Open Contest, Bronze
// Problem 1. Hoof Paper Scissors Minus One
// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

// Logic Used: 
// Find all the symbols that win over both of Elsie's symbols: Let this be Cw
// Let the total number of symbols be Cn
// Now, Bessie can pick one of these winning symbols with any of the losing symbol
// Or pick any two winning symbols. 
// The answer will be Cw * (Cn-Cw) + combinations(Cw, 2)

void printResults(int numSymbols, vector<vector<int>> results) {
    for (int i=0; i<numSymbols; i++) {
        for (int j=0; j<numSymbols; j++) {
            cout << results[i][j] << "\t";
        }
        cout << endl;
    }

}
void readInput( int &numSymbols, int &numGames, vector<vector<int>> &results, vector<vector<int>> &elsieChoices) {
    char result; 

    cin >> numSymbols >> numGames;
    for(int i=0; i<numSymbols; i++) {
        vector<int> row;
        results.push_back(row);
        for (int j=0; j<=i; j++) {
            cin >> result;
            if (result == 'W') {
                results[i].push_back(1);
            } else if (result == 'D') {
                results[i].push_back(0);
            } else {
                results[i].push_back(-1);
            }
        }
    }
    for (int i=0; i<numSymbols; i++) {
        for (int j=i+1; j<numSymbols; j++) {
            results[i].push_back(-1 * results[j][i]);
        }
    }
    int choice;
    for (int i=0; i<numGames; i++) {
        vector<int> elsieChoice;
        for( int j=0; j<2; j++) {
            cin >> choice;
            elsieChoice.push_back(choice);
        }
        elsieChoices.push_back(elsieChoice);
    }
}

int processGame(int numSymbols, vector<vector<int>> &results, vector<int> elsieChoice) {
    set<int> symbolsThatWin[2];
    set<int> winningSet;

    for (int i=0; i<2; i++) {
        for(int j=0; j<numSymbols; j++) {
            int choice = elsieChoice[i]-1;
            //cout << "i:" << choice << "j:" << j << endl;
            if (results[choice][j] == -1) {
                symbolsThatWin[i].insert(j);
            }
        }
    }
    
    std::set_intersection(
        symbolsThatWin[0].begin(), symbolsThatWin[0].end(),
        symbolsThatWin[1].begin(), symbolsThatWin[1].end(),
        std::inserter(winningSet, winningSet.begin()));
    //cout << winningSet.size();
    int nW = winningSet.size();
    return (nW*(2*numSymbols-nW));
}

int main() {
	int numSymbols, numGames;
    vector<vector<int>> results;
    vector<vector<int>> elsieChoices;
    readInput(numSymbols, numGames, results, elsieChoices);
    //printResults(numSymbols, results);

	for (int i=0; i<numGames-1; i++) {
        int solution = processGame(numSymbols, results, elsieChoices[i]);
        cout << solution << endl;
    }
    int solution = processGame(numSymbols, results, elsieChoices[numGames-1]);
    cout << solution;
}

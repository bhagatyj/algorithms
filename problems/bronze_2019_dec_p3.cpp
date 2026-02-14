// USACO Bronze 2019 Dec 3
// Every day, Farmer John milks his 8 dairy cows, named 
// Bessie, Buttercup, Belinda, Beatrice, Bella, Blue, Betsy, and Sue.

#include <bits/stdc++.h>
#include <regex>
using namespace std;

void printCows(const vector<string> &cows) {
    for (auto cow: cows) {
        cout << cow << endl;
    }
}

void printRules(vector<pair<string, string>> &rules) {
    for (auto rule: rules) {
        cout << rule.first << "  " << rule.second << endl;
    }
}

void findNeighbors(vector<pair<string, string>> &rules, 
                    map<string, vector<string>> &neighbors) {
    for (auto rule: rules) {
        neighbors[rule.first].push_back(rule.second);
        neighbors[rule.second].push_back(rule.first);
    }
}

void addCowAndNeighbors(vector<string> &result, string cow,
                       map<string, vector<string>> &neighbors) {
    //cout << "Attempt to add " << cow << endl;
    auto it = find(result.begin(), result.end(), cow);
    if (it == result.end()) {
        //cout << "Added " << cow << endl;
        result.push_back(cow);
        if (neighbors.contains(cow)) {
            for (auto neighbor: neighbors[cow]) {
                addCowAndNeighbors(result, neighbor, neighbors);
            }
        }
    }
}

vector<string> arrange(vector<string> &cows,
                       map<string, vector<string>> &neighbors) {
    vector<string> result;
    for (auto cow: cows) {
        // If a cow has two neighbors and both of them have not been inserted
        // then, we cannot add that cow before at least one of the neighbors.
        if (neighbors[cow].size() != 2) {
            addCowAndNeighbors(result, cow, neighbors);
        }
    }
    return result;
}

int main() {
    vector<string> cows = {"Bessie", "Buttercup", "Belinda", "Beatrice",
                            "Bella", "Blue", "Betsy", "Sue"};
    int count;
    map<string, vector<string>> neighbors;
    vector<pair<string, string>> rules;
    string cow1, must, be, milked, beside, cow2;
    cin >> count;
    for (int i=0; i<count; i++) {
        cin >> cow1 >> must >> be >> milked >> beside >> cow2;
        rules.push_back(make_pair(cow1, cow2));
    }
    sort(cows.begin(), cows.end());
    //printCows(cows);
    //printRules(rules);
    findNeighbors(rules, neighbors);
    vector<string> result = arrange(cows, neighbors);
    printCows(result);
}

// USACO 2020 January Contest, Bronze
// Problem 2. Photoshoot

#include <bits/stdc++.h>
using namespace std;

bool isValueValid(int y, int N, set<int> &valuesSeen) {
    //Check if y is valid
    if ((y <= 0) || (y > N)) {
        return false;
    }
    if (valuesSeen.contains(y)) {
        return false;
    }
    return true;
}

bool findIfXWorks(int x, int N, vector<int> problem, vector<int> &solution) {
    set<int> valuesSeen;
    solution.push_back(x);
    valuesSeen.insert(x);

    for (int i=0; i<N-1; i++) {
        int y = problem[i]-x;
        //cout << " y:" << y << " ";
        //Check if y is valid
        if (!isValueValid(y, N, valuesSeen)) {
            return false;
        } else {
            valuesSeen.insert(y);
            solution.push_back(y);
            x = y;
        }
    }
    if (solution.size() == (long unsigned)N) {
        //cout << x << "works" << endl;
    }
    return true;
}

int main() {
	int N, value; 
    cin >> N;
    vector<int> problem;
    for (auto i=0; i<N-1; i++) {
        cin >> value;
        problem.push_back(value);
    }
    //cout << N << endl;
    vector<int> solution;
    for (int i=1; i<problem[0]; i++) {
        solution.clear();
        //cout << "Trying x = " << i;
        if (findIfXWorks(i, N, problem, solution)) {
            //cout << endl;
            break;
        }
        //cout << endl;
    }
    for (auto i=0; i<N-1; i++) {
        cout << solution[i] << " ";
    }
    cout << solution[N-1];
    //cout << endl;
}

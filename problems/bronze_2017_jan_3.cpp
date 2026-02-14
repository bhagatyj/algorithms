// Greedy Solution

#include <bits/stdc++.h>
using namespace std;

void getInput(int &N, vector<vector<bool>> &matrix) {
    string input;
    cin >> N;
    for (int i=0; i<N; i++) {
        vector<bool> row;
        cin >>input;
        for(int j=0; j<N; j++) {
            if (input[j] == '0') {
                row.push_back(false);
            } else {
                row.push_back(true);
            }
        }
        matrix.push_back(row);
    }
}

void print(int N, vector<vector<bool>> &matrix) {
    for (int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

void flip(vector<vector<bool>> &matrix, int row, int col) {
    for (int i=0; i<=row; i++) {
        for(int j=0; j<=col; j++) {
            matrix[i][j] = !matrix[i][j];
        }
    }
}

pair<int, int> findRowCol(int N, vector<vector<bool>> &matrix) {
    // Find last row that is flipped.
    // In that row, find last col that is flipped.
    for (int i=N-1; i>=0; i--) {
        for (int j=N-1; j>=0; j--) {
            if (matrix[i][j] == true) {
                return(make_pair(i, j));
            }
        }
    }
    return make_pair(-1,-1);
}

int main() {
    int N;
    int count = 0;
    vector<vector<bool>> matrix;
    getInput(N, matrix);
    //print(N, matrix);
    //flip(matrix, 2, 2);
    //print(N, matrix);

    pair<int, int> allDone = make_pair(-1, -1);
    pair <int, int> nextOp = findRowCol(N, matrix);
    while(  nextOp != allDone) {
        count++;
        flip(matrix, nextOp.first, nextOp.second);
        nextOp = findRowCol(N, matrix);
    }
    cout << count;
}

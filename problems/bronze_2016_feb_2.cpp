#include <bits/stdc++.h>
using namespace std;

void getInput(int &count, vector<int> &values) {
    int value;
    cin >> count;
    for(int i=0; i<count; i++) {
        cin >> value;
        values.push_back(value);
    }
}

int process(int count, vector<int> &values) {
    vector<int> multiplier;
    vector<int> distances;
    for(int i=0; i<count; i++) {
        multiplier.push_back(i);
    }
    for (int start=0; start<count; start++) {
        int distance = 0;
        for (int i=0; i<count; i++) {
            int index = (start + i) % count;
            distance += values[i] * multiplier[index];
        }
        distances.push_back(distance);
    }
    sort(distances.begin(), distances.end());
    return distances[0];
}

int main() {
    int count;
    vector<int> values;

    getInput(count, values);
    int ans = process(count, values);
    cout << ans;

}

/*
 * Problem:
 * https://www.hackerrank.com/challenges/merging-communities
 * People connect with each other in a social network. A connection between 
 * Person  I and Person  J is represented as M I J. 
 * When two persons belonging to different communities connect, 
 * the net effect is the merger of both communities which  and  belongs to.
 *
 * At the beginning, there are  people representing  communities. 
 * Suppose person  1 and  2 connected and later  2 and  3 connected, then 
 * 1, 2 and 3 will belong to the same community.
 *
 * There are two type of queries:
 *  communities containing person  and  merged (if they belong to different communities).
 *  print the size of the community to which person  belongs.
 *
 */

#include <cmath>
#include <map>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

map<int, int> root;
map<int, int> groupCount;

int
getRoot(int x) {
    while ( (root[x] != x) ) {
        x = root[x];
    } 
    return x;
}

void
join(int pA, int pB) {
    int rootA, rootB, rootAB;

    // Find A's root
    rootA = getRoot(pA);
    rootB = getRoot(pB);
    rootAB = min(rootA, rootB);
    root[rootA] = rootAB;
    root[rootB] = rootAB;
    groupCount[rootAB] = groupCount[rootA] + groupCount[rootB];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int numPeople, numQueries;
    int pA, pB;
    char c;
    cin >> numPeople >> numQueries ;
    for( auto i=0; i<numQueries; i++) {
        root[i] = i;
        groupCount[i] = 1;
    }
    for( auto i=0; i<numQueries; i++) {
        cin >> c;
        if ( c == 'Q' ) {
            cin >> pA;
            cout << groupCount[getRoot(pA)] << endl;
        } else {
            cin >> pA >> pB;
            join( pA, pB);
        }
    }
    return 0;
}



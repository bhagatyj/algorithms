#include "graph.h"

// Getting the graph input is as follows:
//                  <number-of-vertices>
// adj-list for V0: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// adj-list for V1: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// adj-list for V2: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// and so on...
//
// For example:
/*
4
2 1 50 2 20
0
2 1 15 3 10
0
*/
// would imply
//
//     1 <--50-- 0 ---20---> 2 ----10---->3 
//     ^                     |
//     |                     |
//     ---------15-----------

using namespace std;
Graph * getInput() {
    int numV, numE, vertex, dist, i, j;

    cin >> numV;
    class Graph *G = new class Graph(numV);

    for( i=0; i<numV; i++ ) {
        cin >> numE;
        vector <class Adj> adjv;
        for ( j=0; j<numE; j++ ) {
            cin >> vertex >> dist;
            class Adj *adj = new class Adj( vertex, dist );
            adjv.push_back(*adj);
        }
        G->__adj.push_back(adjv);
    }
    return G;
}

int main() {
    class Graph *G = getInput();
    G->printGraph();
    G->dfs();
    G->parent_dfs();
    G->bfs();

    cout << "Start Djikstra " << endl;
    G->djikstra( 0);
}

#include "graph.h"

// Getting the graph input is as follows:
//                  <number-of-vertices>
// adj-list for V0: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// adj-list for V1: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// adj-list for V2: <number-of-edges> <edge-0-other-vertex> <edge-0-len> and so on..
// and so on...
//
// For example:
//
// 3
// 2 1 10 2 20
// 0
// 1 1 15
//
// would imply
//
//     1 <--10-- 0 ---20---> 2
//     ^                     |
//     |                     |
//     ----------------------

using namespace std;
Graph * getInput() {
    int numV, numE, vertex, dist, i, j;

    cin >> numV;
    class Graph *G = new class Graph(numV);

    for( i=0; i<numV; i++ ) {
        cin >> numE;
        list <class Adj> adjv;
        for ( j=0; j<numE; j++ ) {
            cin >> vertex >> dist;
            // Note:: The implementation of push_back does a
            // copy_construct. Hence, it is ok to pass an 
            // object from the stack.
            class Adj adj( vertex, dist );
            G->__adjs[i].push_back(adj);
        }
    }
    return G;
}

int main() {
    class Graph *G = getInput();
    G->printGraph();
    G->dfs();
    G->parent_dfs();
    G->bfs();
    cout << G->find_if_cyclic() << endl;
}

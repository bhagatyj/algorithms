#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;
class Graph;

class Adj {
        int node;
        int distance;
        friend class Graph;
    public:
        Adj(int n, int d) : node(n), distance(d) {};
};

class Graph {
        vector< vector<Adj> > adjvv;
    public:
        Graph();
        void topoSort();
        void topoSortDfs( int vertex, map<int, bool> &visitedMap,
                            stack<int> *topoStack );
};

// For this topological problem, we need an unidirectional graph
// with specific conditions. Handcraft the creation of the graph.
//    
//     _______________
//    |               |
//    |               V
//    0--->1--->2 <---4
//    |    |          |
//    |    |          |
//    V    |          |
//    3 <-------------
//
Graph::Graph() {
    vector< Adj> adjv;

    adjv.push_back( Adj(1, 1) ); 
    adjv.push_back( Adj(3, 1) );
    adjv.push_back( Adj(4, 1) );
    adjvv.push_back( adjv );
    adjv.clear();

    adjv.push_back( Adj(2,1) );
    adjv.push_back( Adj(3,1) );
    adjvv.push_back( adjv );
    adjv.clear();
    
    adjvv.push_back( adjv );
    adjv.clear();

    adjvv.push_back( adjv );
    adjv.clear();

    adjv.push_back( Adj(2,1) );
    adjv.push_back( Adj(3,1) );
    adjvv.push_back( adjv );

}
void
Graph::topoSortDfs( int vertex, map<int, bool> &visitedMap, stack<int> *topoStack ) {

    for( auto it = adjvv[vertex].begin(); it != adjvv[vertex].end(); it++ ) {
        cout << "visiting node:" << it->node << endl;
        if( !visitedMap[ it->node ] ) {
            visitedMap[it->node] = true;
            topoSortDfs( it->node, visitedMap, topoStack );
        }
    }
    // Add to stack when I have nowhere else to visit
    topoStack->push( vertex );
}

void
Graph::topoSort() {
    map< int, bool > visitedMap;
    stack<int> topoStack;
    int vertex;

    for( vertex = 0; vertex< adjvv.size(); vertex++ ) {
        cout << "outer visiting node:" << vertex << endl;
        if( !visitedMap[ vertex ] ) {
            visitedMap[vertex] = true;
            topoSortDfs( vertex, visitedMap, &topoStack );
        }
    }

    // Print out the stack.
    while( ! topoStack.empty() ) {
        vertex = topoStack.top();
        topoStack.pop();
        cout << vertex << endl;
    }
}
            
int 
main() {
    Graph G;
    G.topoSort();
}

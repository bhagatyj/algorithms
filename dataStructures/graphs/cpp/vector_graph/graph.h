#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

class Graph;
class DNode;

class Adj {
    int  __node;
    int  __distance;
    friend class Graph;
public:
    Adj( int node, int distance ) {
        __node = node;
        __distance = distance;
    }
        
};

class Graph {
    int  __numVertices;

public:
    vector<vector<class Adj> > __adj;
    Graph( int numV ) {
        __numVertices = numV;
    }
    void printGraph();
    void dfs_visit( int node, map<int, bool> &visitedNodes);
    void dfs();
    void parent_dfs_visit( int node, map<int, char> &visitedNodes);
    void parent_dfs();
    void bfs_visit( int node, map<int, bool> &visitedNodes );
    void bfs();
    void djikstra( int source );
    int findMin( vector<DNode> distances );
};

void 
Graph::printGraph() {
    vector<vector<class Adj> >::iterator it;
    vector<class Adj>::iterator itt;
    int index = 0;

    for (it = __adj.begin(); it != __adj.end(); it++ ) {
        cout << "At vertex:" << index << endl;
        for ( itt = it->begin(); itt != it->end(); itt++ ) {
            cout << "\tnode:" << itt->__node
                 << " dist:" << itt->__distance;
        }
        cout << endl;
        index++;
    }
}

// DFS:
//
void
Graph::dfs_visit( int node, map<int, bool> &visitedNodes) {

    vector<class Adj>::iterator it;
    for ( it = __adj[node].begin(); it != __adj[node].end(); it++ ) {
        if ( ! visitedNodes[it->__node] ) {
            cout << "Visiting Node: " << it->__node << endl;
            visitedNodes[ it->__node ] = true;
            dfs_visit( it->__node, visitedNodes );
        }
    }

}

void
Graph::dfs() {
    map<int, bool> visitedNodess;
    int node;
    
    for ( node = 0; node < __numVertices; node++ ) {
        if ( !visitedNodess[node] ) {
            cout << "Visiting Node: " << node << endl;
            visitedNodess[node] = true;
            dfs_visit( node, visitedNodess );
        }
    }
}

void
Graph::parent_dfs_visit( int node, map<int, char> &parentNode) {

    vector<class Adj>::iterator it;
    for ( it = __adj[node].begin(); it != __adj[node].end(); it++ ) {
        if ( ! parentNode[it->__node] ) {
            cout << "Visiting Node: " << it->__node
                 << " from Node:" << node << endl;
            parentNode[ it->__node ] = 'a' + node;
            parent_dfs_visit( it->__node, parentNode );
        }
    }

}

void
Graph::parent_dfs() {
    map<int, char> parentNode;
    int node;
    
    for ( node = 0; node < __numVertices; node++ ) {
        if ( !parentNode[node] ) {
            cout << "Visiting Node: " << node << endl;
            parentNode[node] = 'r';
            parent_dfs_visit( node, parentNode );
        }
    }
}

// BFS:
//
void
Graph::bfs_visit( int node, map<int, bool> &visitedNodes ) {

    vector<class Adj>::iterator it;
    queue<int> nodesAtThisLevel;

    nodesAtThisLevel.push( node );
    while ( ! nodesAtThisLevel.empty() ) {
        node = nodesAtThisLevel.front();
        nodesAtThisLevel.pop();
        for ( it = __adj[node].begin(); it != __adj[node].end(); it++ ) {
            if ( !visitedNodes[it->__node] ) {
                cout << "Visiting Node: " << it->__node << endl;
                nodesAtThisLevel.push( it->__node );
                visitedNodes[it->__node] = true;
            }
        }
    }

}

void
Graph::bfs() {
    map<int, bool> visitedNodes;
    int node;
    
    for( node=0; node<__numVertices; node++ ) {
        if ( !visitedNodes[node] ) {
            cout << "Visiting Node: " << node << endl;
            visitedNodes[node] = true;
            bfs_visit( node, visitedNodes );
        }
    }
}

// Find the min distance from the source node to every other node.
//
// Create a Djikstra data structure
class DNode {
        int node;
        int prevNode;
        int cost;
        bool visitComplete;
        friend class Graph;
    public:
        DNode( int n ) : node(n), prevNode(-1), 
                  cost(std::numeric_limits<int>::max()), visitComplete(false) {};
        bool operator< ( DNode other ) {
            // Return the opposite as we need a minHeap
            return ( cost > other.cost );
        }
        int getCost() { return cost; }
};

int
Graph::findMin( vector<DNode> distances ) {

    // Find the minimum Node from the nodes that has not been visited so far.
    // If all the nodes have been visited already, return end.
    int minCost = std::numeric_limits<int>::max();
    int size = distances.size();
    int minIndex = -1;

    for( int i=0; i<size; i++) {
        if( (distances[i].getCost() < minCost) &&
            ( not distances[i].visitComplete) ) {
            minCost = distances[i].getCost();
            minIndex = i;
        }
    }
    return minIndex;

}

void
Graph::djikstra( int source ) {

    // Initialize all the DNodes
    vector<DNode> distances;
    vector<DNode> results;
    int minNode;

    if( source >= __numVertices ) { cout << "Input Error" << endl; return; }

    for( int i=0; i<__numVertices; i++) {
        distances.push_back( DNode( i ) );
    }

    // Initialize the source
    distances[source].prevNode = source;
    distances[source].cost = 0;

    // Find the minCost Node.
    minNode = findMin( distances );

    while( minNode != -1 ) {
        distances[minNode].visitComplete = true;
        cout << "Can visit node " << minNode 
             << " with a distance of " 
             << distances[minNode].getCost() << endl;
        results.push_back( distances[minNode] );
        int minNodeDistance = distances[minNode].getCost();

        // Loop through all the vertices and update distances.
        for( vector<class Adj>::iterator it = __adj[minNode].begin();
                                it!= __adj[minNode].end(); it++ ) {
            if ( distances[it->__node].cost > ( minNodeDistance + it->__distance ) ) {
                distances[it->__node].cost = minNodeDistance + it->__distance;
                distances[it->__node].prevNode = minNode;
            }
        }
        // Find the next minimum
        minNode = findMin( distances );
    }
}

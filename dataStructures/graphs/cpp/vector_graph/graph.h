#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Graph;

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

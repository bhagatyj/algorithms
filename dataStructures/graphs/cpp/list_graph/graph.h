#include <iostream>
#include <vector>
#include <list>
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
    vector< list<class Adj> >  __adjs;
    Graph( int numV ) {
        __numVertices = numV;
        __adjs.resize( numV );
    }
    void printGraph();
    void dfs_visit( int node, map<int, bool> &visitedNodes);
    void dfs();
    void parent_dfs_visit( int node, map<int, char> &visitedNodes);
    void parent_dfs();
    void bfs_visit( int node, map<int, bool> &visitedNodes );
    void bfs();
    bool dfs_color_visit( int i, vector<int> &vertexColors );
    bool find_if_cyclic();
};

void 
Graph::printGraph() {
    vector<list<class Adj> >::iterator it;
    list<class Adj>::iterator itt;
    int index = 0;

    for (it = __adjs.begin(); it != __adjs.end(); it++ ) {
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

    list<class Adj>::iterator it;
    for ( it = __adjs[node].begin(); it != __adjs[node].end(); it++ ) {
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

    list<class Adj>::iterator it;
    for ( it = __adjs[node].begin(); it != __adjs[node].end(); it++ ) {
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

    list<class Adj>::iterator it;
    queue<int> nodesAtThisLevel;

    nodesAtThisLevel.push( node );
    while ( ! nodesAtThisLevel.empty() ) {
        node = nodesAtThisLevel.front();
        for ( it = __adjs[node].begin(); it != __adjs[node].end(); it++ ) {
            if ( !visitedNodes[it->__node] ) {
                cout << "Visiting Node: " << it->__node << endl;
                nodesAtThisLevel.push( it->__node );
                visitedNodes[it->__node] = true;
            }
        }
        nodesAtThisLevel.pop();
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

#define WHITE 1
#define GRAY  2
#define BLACK 3
bool
Graph::dfs_color_visit( int i, vector<int> &vertexColors ) {
    list<class Adj>::iterator it;    

    for (it = __adjs[i].begin(); it != __adjs[i].end(); it++) {
        if ( vertexColors[it->__node] == GRAY ) {
            return true;
        }
        if ( vertexColors[it->__node] == BLACK ) {
            continue;
        }
        // Visit now
        vertexColors[it->__node] = GRAY;
        dfs_color_visit( it->__node, vertexColors );
    }
    // All my children done. 
    // Change color to black.
    vertexColors[it->__node] = BLACK;
    return false;
}

bool
Graph::find_if_cyclic() {

    int i;
    vector<int> vertexColors;
    vertexColors.resize( __numVertices );
    for (i=0; i<__numVertices; i++) {
        vertexColors[i] = WHITE;
    }

    for (i=0; i<__numVertices; i++) {
        if ( vertexColors[i] == WHITE ) {
            vertexColors[i] = GRAY;
            if ( dfs_color_visit(i, vertexColors) ) {
                return true;
            }
        }
    }
    return false;
}

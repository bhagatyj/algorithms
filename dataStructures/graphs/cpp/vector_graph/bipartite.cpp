#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "assert.h"

using namespace std;

#define GROUP_A 1
#define GROUP_B 2
int
getOtherGroup( int group ) {
    if( group == GROUP_A ) { return GROUP_B; }
    if( group == GROUP_B ) { return GROUP_A; }
    return -1;
}

bool
isBipartiteDfsVisit( int vertex, vector<vector<int> > &graph,
                     map<int, int> &visited, int group ) {

    int otherGroup = getOtherGroup( group );

    // Handle Revisits..
    if( visited[ vertex ] ) {
        // Are we revisiting a vertex with the same group number ?
        // If so, just return.
        if( visited[vertex] == group ) {
            return true;
        }
        // Are we revisiting a vertex with the purpose of adding it
        // to opposite group ? If so, return false.
        if( visited[vertex] == getOtherGroup( group ) ) {
            return false;
        }
        // If we have visited the node already, 
        // it has to be one of the above cases.
        assert( 0 );
    }
    
    cout << "Vertex: " << vertex << " Group: " << group << endl;
    visited[ vertex ] = group;
    for( auto it=graph[vertex].begin(); it!= graph[vertex].end(); it++ ) {
        if( not isBipartiteDfsVisit( *it, graph, visited, otherGroup ) ) {
            return false;
        }
    }
    return true;
}

bool
isBipartite( vector< vector< int> > & graph) {

    map< int, int > visited;
    int group = GROUP_A;

    for( int vertex=0; vertex<graph.size(); vertex++ ) {
        if( not visited[vertex] ) { 
            if( not isBipartiteDfsVisit( vertex, graph, visited, group ) ) {
                return false;
            }
        }
    }
    return true;
}

void
printGraph( vector< vector<int> > &graph ) {
    for( int i=0; i<graph.size(); i++ ) {
        if( not graph[i].empty() ) {
            for( auto it2 = graph[i].begin(); it2 != graph[i].end(); it2++ ) {
                cout << *it2 << "\t" ;
            }
        }
        cout << endl;
    }
}

int main( ) {

    vector< vector<int> > graph;
    vector<int> adj;

    // 0 : 2, 3
    adj.push_back( 2 ); adj.push_back( 3 );
    graph.push_back( adj );
    
    // 1 : 3
    adj.clear(); adj.push_back( 3 ); adj.push_back( 0 );
    graph.push_back( adj );
    
    // 2 : 0
    adj.clear(); adj.push_back( 0 );
    graph.push_back( adj );

    // 3 : 0, 1
    adj.clear(); adj.push_back( 0 ); adj.push_back( 1 );
    graph.push_back( adj );

    printGraph( graph );
    bool bipartite = isBipartite( graph );
    cout << "BiPartite: " << bipartite << endl;
}

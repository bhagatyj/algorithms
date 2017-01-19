#include <map>
#include <assert.h>
#include <random>
#include <iostream>
#include <vector>

using namespace std;
class UndirGraph;
class Adj {
    protected:
        int vertex;
        int distance;
        friend class UndirGraph;
    public:
        Adj(int v, int d): vertex(v),distance(d) {};
};
class Edge {
    public:
        int a;
        int b;
        int distance;
        Edge(int _a, int _b, int d) : a(_a), b(_b), distance(d) {};
        bool operator < ( Edge const &b ) { return (distance < b.distance); }
        friend bool operator <( const Edge &a, const Edge &b ) {
                return (a.distance > b.distance ); 
        }
};
    
class UndirGraph {
    protected:
        vector<vector<Adj> > adjvv;
    public:
        UndirGraph( int numVertices) { adjvv.resize( numVertices ); };
        void addEdge( Edge e );
        UndirGraph( int numVertices, double averageEdgesPerVertex );
        bool isCyclicDfsTraverse(int vertex, map<int, int> &vertexColor);
        bool isCyclic();
        void printUndirGraph();
        UndirGraph getMST();
};

UndirGraph::UndirGraph( int numVertices, double averageEdgesPerVertex ) {
    map<pair<int,int>, bool> edges;
    srand(time(NULL));
    for( int i=0; i<numVertices; i++) {
        vector<Adj> adjv;
        adjvv.push_back(adjv);
    }
    for( int i=0; i<numVertices; i++) {
        for( int j=0; j<numVertices; j++) {
            if ( edges[pair<int,int>(i,j)] == true ) { continue; }
            if ( i != j ) {
                double d1 = rand()*1.0/RAND_MAX;
                if ( d1 < averageEdgesPerVertex ) {
                    int distance = rand() % 100;
                    Adj adj1(j, distance);
                    adjvv[i].push_back(adj1);
                    Adj adj2(i, distance);
                    adjvv[j].push_back(adj2);
                    edges[pair<int,int>(i,j)] = true;
                    edges[pair<int,int>(j,i)] = true;
                }
            }
        }
    }
}
        
void
UndirGraph::addEdge( Edge e ) {
    adjvv[e.a].push_back( Adj(e.b, e.distance) );    
    adjvv[e.b].push_back( Adj(e.a, e.distance) );    
}

void
UndirGraph::printUndirGraph() {
    for( int i=0; i < adjvv.size(); i++ ) {
        cout << "\tVertex : " << i << endl;
        for( auto it=adjvv[i].begin(); it != adjvv[i].end(); it++ ) {
            cout << "\t\t vertex:" << it->vertex << " distance:" 
                    << it->distance << endl;
        }
    }
}

vector<Edge> 
pruneEdges( vector<Edge> &edges, vector<bool> &addedVertices ) {

    vector<Edge> newEdges;

    // Remove all Edges that are not needed anymore.
    for( auto it= edges.begin(); it!= edges.end(); it++ ) { 
        if ( !addedVertices[it->a] || !addedVertices[it->b] ) {
            newEdges.push_back(*it);
        }
    }
    return newEdges;
}

void
printEdges(vector<Edge> const &edges)
{
    for( Edge e : edges ) {
        cout << "a:" << e.a << " b:" << e.b << 
            " d:" << e.distance << endl;
    }

}

UndirGraph
UndirGraph::getMST() {
    UndirGraph mst( adjvv.size() );
    int i, mstEdges = 0;
    vector<Edge> edges;
    vector<bool> addedVertices;
    bool toAdd;
    int nextVertex = 0;
    addedVertices.resize( adjvv.size() );
    do {
        //cout << "Picked vertex " << nextVertex << endl;
        addedVertices[nextVertex] = true;
        for( auto it = adjvv[nextVertex].begin(); it != adjvv[nextVertex].end(); it++) {
            Edge e(nextVertex, it->vertex, it->distance);
            edges.push_back(e);
        }
        edges = pruneEdges( edges, addedVertices );
        if( edges.empty() ) { break; }
        make_heap( edges.begin(), edges.end() );
        // printEdges(edges);
        Edge nextEdge = edges.front();
        pop_heap( edges.begin(), edges.end() );
        edges.pop_back();

        //cout << "Picked Edge " << nextEdge.a << " " << nextEdge.b << endl;
        if ( addedVertices[nextEdge.a] ) {
            nextVertex = nextEdge.b; 
        } else {
            nextVertex = nextEdge.a; 
        }
        mst.addEdge( nextEdge );
        mstEdges++;
        if ( mstEdges == adjvv.size() - 1 ) {
            // Found our MST
            break;
        }
    } while ( mstEdges < (adjvv.size() - 1 ) );
    if( mstEdges < (adjvv.size() - 1) ) {
        cout << "could not form mst" << endl;
        return UndirGraph::UndirGraph(adjvv.size());
    } else {
        return mst;
    }
}

// Run a DFS and add the edges to a min-heap.
// Get the smallest edge and add to new UndirGraph and 
// try unionIfNonCyclic.
// When the number of edges reach the goal ("numberOfVertices-1"),
//      or the heap is over
//          stop.
// If the heap was over, no MST can be formed.
// If we reached the goal, we have an MST.
void
tryUndirGraph(int numVertices, double numEdgesPerVertex) {
    vector<Edge> edges;
    UndirGraph G(numVertices, numEdgesPerVertex);
    G.printUndirGraph();
    UndirGraph G2 = G.getMST();
    cout << "MST " << endl;
    G2.printUndirGraph();
    cout << "Done " << endl;

}

int main() {
    tryUndirGraph(5, 1.5/4);
    //tryUndirGraph(8, 1.5/8);
}
    


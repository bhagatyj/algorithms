#include <map>
#include <assert.h>
#include <random>
#include <iostream>
#include <vector>

using namespace std;
class Graph;
class Adj {
    protected:
        int vertex;
        int distance;
        friend class Graph;
    public:
        Adj(int v, int d): vertex(v),distance(d) {};
};
class Graph {
    protected:
        vector<vector<Adj> > adjvv;
    public:
        Graph( int numVertices, int numEdges );
        bool isCyclicDfsTraverse(int vertex, map<int, int> &vertexColor);
        bool isCyclic();
        void printGraph();
};

#define WHITE 0
#define GRAY  1
#define BLACK 2

bool
Graph::isCyclicDfsTraverse(int vertex, map<int, int> &vertexColor) {

    cout << "Visiting Node " << vertex << endl;
    for( auto it=adjvv[vertex].begin(); it!=adjvv[vertex].end(); it++ ) {
        if( vertexColor[it->vertex] == GRAY ) {
            cout << "Met node " << it->vertex << " again." << endl;
            return true;
        }
        vertexColor[it->vertex] = GRAY;
        if (isCyclicDfsTraverse( it->vertex, vertexColor ) ) { 
            return true;
        }
        vertexColor[it->vertex] = BLACK;
    }
    return false;
}

bool
Graph::isCyclic() {
    map<int, int> vertexColor;

    for( auto i=0; i<adjvv.size(); i++) {
        // If color is black, we have already visited this node and children.
        // If color is white, we are visiting it first time.
        // The color can never be gray at this point as we just picked up this node.
        if( vertexColor[i] == GRAY ) { assert(0); }
        if( vertexColor[i] == WHITE ) {
            vertexColor[i] = GRAY;
            if ( isCyclicDfsTraverse(i, vertexColor) ) {
                return true;
            }
            vertexColor[i] = BLACK;
        }
    }
    return false;
}

Graph::Graph( int numVertices, int averageEdgesPerVertex ) {
    srand(time(NULL));
    for( int i=0; i<numVertices; i++) {
        // Toss and see if this vertex has edges 
        int numEdges = rand() % averageEdgesPerVertex;
        vector<Adj> adjv;
        for( int j=0; j<numEdges; j++) {
            int vertex = rand() % numVertices;
            int distance = rand() % 100;
            Adj adj(vertex, distance);
            adjv.push_back(adj);
        }
        adjvv.push_back(adjv);
    }
}
        
void
Graph::printGraph() {
    for( int i=0; i < adjvv.size(); i++ ) {
        cout << "Vertex : " << i << endl;
        for( auto it=adjvv[i].begin(); it != adjvv[i].end(); it++ ) {
            cout << "\t\t vertex:" << it->vertex << " distance:" 
                    << it->distance << endl;
        }
    }
}

void
tryGraph(int numVertices, int numEdgesPerVertex) {
    Graph G(numVertices, numEdgesPerVertex);
    G.printGraph();
    bool isCyclic = G.isCyclic();
    cout << "This graph " << ( isCyclic ? " cyclic." : " not cyclic." ) << endl;
}

int main() {
    tryGraph(4, 1);
    tryGraph(10, 2);
    tryGraph(10, 4);
}
    


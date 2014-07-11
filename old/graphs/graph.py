import sys
import json


class Graph():
    count = 0

    @staticmethod
    def myName():
        Graph.count += 1
        return "Graph_%d" %Graph.count

    def baseInit(self, numV):
        self.numV = numV
        self.numE = 0
        self.adj = list()
        self.name = Graph.myName()
        for i in range(numV):
            self.adj.append(list())


    def __init__(self, *args, **kwargs):
        """ vertices: Create a V-vertex graph. No edges"""
        """ input: Read a graph from a string.
        Format: { "numE": "<numE>", 
                  "edges": [ "V1:V2", 
                             "V3:V4"
                              ...]
                  }
        """
        self.input = kwargs.get('inputStr', None)
        if (self.input):
            js = json.loads(self.input)
            self.baseInit(int(js["numV"]))
            if js["edges"]:
                for edge in js["edges"]:
                    vertices = edge.split(":")
                    v1 = int(vertices[0])
                    v2 = int(vertices[1])
                    self.addEdge(v1, v2)
        else:
            self.baseInit(kwargs.get('numV', 0))

    def V(self):
        """ Return number of vertices"""
        pass

    def E(self):
        """ Return number of vertices"""
        pass

    def addEdge(self, v1, v2):
        """ Adds Edges"""
        if ((v1 > self.numV) or (v2 > self.numV)):
            raise IndexError
        self.adj[v1].append(v2)
        self.adj[v2].append(v1)
        self.numE += 1


    def __iter__(self, v):
        return self

    def next(self):
        """vertices adjacent to v"""
        pass

    def __str__(self):
        """ String Representation """
        header = "Name:%s Vertices:%d Edges:%d\n" \
            %(self.name, self.numV, self.numE)
        edgeStr = ""
        edges = ""
        index = 0
        for adjList in self.adj:
            if len(adjList):
                edgeStr = "Neighbors of Vertex %d :" %(index)
                for j in adjList:
                    edgeStr += " %d" %j
                edges += edgeStr + "\n"
            index += 1
        return header + edges


if __name__ == "__main__":
    print "Hello world"
    g = Graph()
    print g
    g = Graph(numV=3)
    print g
    jsonSte = '{"numV":"3", "numE": "3", "edges": ["0:2", "1:2", "0:1"]}'
    g = Graph(inputStr =jsonSte)
    print g

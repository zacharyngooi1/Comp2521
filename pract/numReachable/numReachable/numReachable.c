
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"


int reach(Graph g, int src, int *visited);

int numReachable(Graph g, int src) {
    int *visited = calloc((unsigned int) GraphNumVertices(g), sizeof(int));
    for (int t = 0; t< GraphNumVertices(g); t++) {
        visited[t] = -1;
    }
    int final = reach(g,src,visited);
    free(visited);
   return final;
}

int reach(Graph g, int src, int *visited) {
    int total_nodes = 0;
    visited[src] = 1;

    for (int x = 0; x < GraphNumVertices(g); x ++) {
        if (GraphIsAdjacent(g,src,x) && visited[x] == -1) {
            
            int count = reach(g,x, visited);
            total_nodes = total_nodes + count;
        }
    }
    total_nodes = total_nodes + 1;
	return total_nodes;
}

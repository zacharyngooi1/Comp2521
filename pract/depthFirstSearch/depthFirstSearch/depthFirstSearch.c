
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void reach(Graph g, int src, int *visited);

void depthFirstSearch(Graph g, int src) {
    int *visited = calloc((unsigned int) GraphNumVertices(g), sizeof(int));
    for (int t = 0; t< GraphNumVertices(g); t++) {
        visited[t] = -1;
    }
    printf("%d ", src);
    reach(g, src,visited);
    free(visited);
    
}   

void reach(Graph g, int src, int *visited) {
    visited[src] = 1;
    for (int x = 0; x < GraphNumVertices(g); x ++) {
        if (GraphIsAdjacent(g,src,x) && visited[x] == -1) {
            printf("%d ", x);
            visited[x] = src;
            reach(g,x, visited);
        }
    }
}
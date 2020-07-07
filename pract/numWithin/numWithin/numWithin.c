
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	Queue new_queue = QueueNew();
    QueueEnqueue(new_queue, src);
    int *visited = calloc((unsigned int) GraphNumVertices(g), sizeof(int));
    for (int x = 0; x<GraphNumVertices(g); x++) {
        visited[x] = -1;
    }
    int *distance = calloc((unsigned int) GraphNumVertices(g), sizeof(int));

    visited[src] = 1;
    distance[src] = 0;
    int curr;
    while (!QueueIsEmpty(new_queue)) {
        curr = QueueDequeue(new_queue);
        for (int f = 0; f < GraphNumVertices(g); f ++) {
            if (GraphIsAdjacent(g,curr,f) && visited[f] == -1) {
                distance[f] = distance[curr] + 1;
                visited[f] = 1;
                QueueEnqueue(new_queue,f);
            }
        }
    }
    int vertex = 0;
    for (int count = 0; count < GraphNumVertices(g); count ++) {
        if (distance[count] > 0 && distance[count] <= dist) {
            vertex ++;
        }
    }
    QueueFree(new_queue);
    free(visited);
    free(distance);
    return vertex + 1;
}


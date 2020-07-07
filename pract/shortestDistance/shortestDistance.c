
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	Queue new_queue = QueueNew();
    QueueEnqueue(new_queue, src);
    int *visited = calloc((unsigned int) GraphNumVertices(g), sizeof(int));
    for (int x = 0; x<GraphNumVertices(g); x++) {
        visited[x] = -1;
    }
    int *distance = calloc((unsigned int) GraphNumVertices(g), sizeof(int));

    visited[src] = 1;
    distance[src] = 0;
    int found = 0;
    int curr;
    while (!QueueIsEmpty(new_queue)) {
        curr = QueueDequeue(new_queue);
        if (curr == dest) {
            found = 1;
        }
        for (int f = 0; f < GraphNumVertices(g); f ++) {
            if (GraphIsAdjacent(g,curr,f) && visited[f] == -1) {
                distance[f] = distance[curr] + 1;
                visited[f] = 1;
                QueueEnqueue(new_queue,f);
            }
        }
    }
    int smallest = 999;
    for (int count = 0; count < GraphNumVertices(g); count ++) {
        if (count == dest) {
            if (distance[count] <= smallest) {
                smallest = distance[count];
            }
        }
    }
    QueueFree(new_queue);
    free(visited);
    free(distance);
    if (smallest == 999 || found == 0){
        return -1;
    }
    return smallest;
}


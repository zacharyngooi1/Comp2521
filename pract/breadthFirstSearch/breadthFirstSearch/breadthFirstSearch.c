
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
    Queue new_queue = QueueNew();
    QueueEnqueue(new_queue, src);
    int *visited = calloc((unsigned int) GraphNumVertices(g), sizeof(int));
    for (int x = 0; x<GraphNumVertices(g); x++) {
        visited[x] = -1;
    }

    visited[src] = 1;
    int curr;
    while (!QueueIsEmpty(new_queue)) {
        curr = QueueDequeue(new_queue);
        printf("%d ", curr);

        for (int f = 0; f < GraphNumVertices(g); f ++) {
            if (GraphIsAdjacent(g,curr,f) && visited[f] == -1) {
                visited[f] = 1;
                QueueEnqueue(new_queue,f);
            }
        }
    }
    QueueFree(new_queue);
    free(visited);
}


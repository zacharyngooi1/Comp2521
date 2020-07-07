// rankPopularity.c ... implementation of rankPopularity function
// z5228846 -Zachary Ngooi
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/
void reach(Graph g, int src, int *visited, double *mnV);
double inbound(Graph g, int col);
double outbound(Graph g, int row);

void rankPopularity(Graph g, int src, double *mnV) {
	// Create array to hold visited nodes
    int *visited = calloc((unsigned int) g->nV, sizeof(int));
    for (int t = 0; t< g->nV; t++) {
        visited[t] = -1;
    }
    // Call function to check if node is reachable and insert
    // into array
    reach(g,src,visited,mnV);
    // free created array
    free(visited);
}

void reach(Graph g, int src, int *visited, double *mnV) {
    // Set src to be visited
    visited[src] = 1;
    // Since src is visited and the first src will always be
    // visited, calculate its popularity rank and insert 
    // into the array.
    double popularity = inbound(g,src) / outbound(g,src);
    // Insert into array
    mnV[src] = popularity;
    for (int x = 0; x < g->nV; x ++) {
        // Check for adjacent nodes to the src node that has not
        // been visited yet
        if (adjacent(g,src,x) && visited[x] == -1) {
            // Call function again but with the adjacent value as
            // the new src
            reach(g,x, visited, mnV);
        }
    }
}

double outbound(Graph g, int row) {
    // Set counter
    double counter = 0;
    for (int j=0; j< g->nV; j++){
        if (g->edges[row][j] != 0) {
            counter++;
        }
    }
    // Set counter value to be 0.5 if no links are found
    if (counter == 0) {
        counter = 0.5;
    }
    return counter;
}

// Count inbound links
double inbound(Graph g, int col) {
    // Set counter
    double counter = 0;
    for (int j=0; j< g->nV; j++){
        if (g->edges[j][col] != 0) {
            counter ++;
        }
    }
    return counter;
}
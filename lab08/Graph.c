// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}



// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	int *visited = calloc((unsigned int)g->nV, sizeof(int));
	assert(g != NULL);
	// Create array for visited vertices
	// Set all values in array to be -1
	for (int i = 0; i < g->nV; i++) {
	   visited[i] = -1;
	}
	// Set a int found to be false
	int found = 0;
	// Set your visited in your queue to be your starting vertex
	visited[src] = src;
	// Create a new empty queue
	Queue new_queue = newQueue();
	// Enqueue your src into your newly created queue
	QueueJoin(new_queue, src);
	// Set a integer for the number of hops
	int hops = 0;
	// Run until queue is empty
	while (!QueueIsEmpty(new_queue)) {
		// Set the current vertex as the one to be dequeued
		Vertex curr_vertex = QueueLeave(new_queue);
		// Set as found if the curr_vertex if my destination
		if (curr_vertex == dest) {
			found = 1;
			break;
		}
		else {
			for (int j = 0; j < g->nV; j++) {
				// Check for the 3 conditions before setting the vertex
				if (g->edges[curr_vertex][j] != 0 && visited[j] == -1 && g->edges[curr_vertex][j] <= max) {
					visited[j] = curr_vertex;
					// Set j as current vertex
					QueueJoin(new_queue, j);
				}
			}
		}
	}
	// Free the memory of the created queue as the queue is no longer needed.
	dropQueue(new_queue);
	// This means destination was not found
	if (visited[dest] == -1){
	   return 0;
   }
   // if found == 1 queue and sort
	if (found == 1) {
		int current_pos = dest;
		// Create a temp pointer
		int *temp = calloc((unsigned int)g->nV, sizeof(int));
		// count the number of hops needed
		while (current_pos != src) {
		temp[hops] = current_pos;
		hops++;
		// set the current pos as the same index as the visited array
		current_pos = visited[current_pos];
		}
		temp[hops] = src;
		// Set a int for number of hops
		int n = hops;
		for(int i = 0; i <= hops; i++) {
		// Call temp
		path[i] = temp[n];
		n--;
		}
		// Free temp
		free(temp);
	}
	// Free empty visited array
	free(visited);
	// Return number of hops
	return hops + 1;
}

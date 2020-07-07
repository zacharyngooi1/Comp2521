#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#define MAX_INVERTED 1000
#define MAX_CHAR 1024

typedef struct graph_struct {
    int nV;
    int nE;
    double **edges;
} *Graph;
 
#define MAX_CHAR 1024

/////////////////////////////////////////////////////////
//                  Graph functions                    //
/////////////////////////////////////////////////////////

// Creates a graph 
Graph create_graph(int num_of_vertices);
// Prints graph to terminal
void print_array(Graph g, int num_urls, char **array);
// Frees mem for graph
void dropGraph (Graph g);
/////////////////////////////////////////////////////////
//                  file functions                     //
/////////////////////////////////////////////////////////

// Opens urls for in array and adds .txt to them
void open_file(char** array, int number_of_urls, Graph graph_struct);
// Opens each inner url
void open_inner(char **array, int number_of_urls, Graph graph_struct, char *outer_url, int row);
// Finds positon of url in row
int find_position(char** array, char* find_word, int number_of_urls);
// Outputs ranking to file
void print_to_file(double *pr_array, int num_urls, char** url_array, Graph g);

/////////////////////////////////////////////////////////
//               Calculation functions                 //
/////////////////////////////////////////////////////////

// Calculates outbound links 
double outbound(Graph graph_struct, int num_urls_in_collection, int row);
// Calculates Inbound links 
double inbound(Graph graph_struct, int num_urls_in_collection, int col);
// Sum the outbound links for a given url in the graph.
double total_outbound(int src, Graph g);
// Sum the inbound links for a given url in the graph.
double total_inbound(int src, Graph g);
// Calc weight out
double calc_weight_out(int source, int destination, Graph graph_struct);
// Calc weight in
double calc_weight_in(int source, int destination, Graph graph_struct);
// Creates neccessary arrays for each iteration
void PageRankW(Graph g, double d, double diff_in_pr, int max_iteration, char ** url_array);
// Calculates weighted page rank and outputs to file
void calculate_wpr(double diff_in_pr, int max_iteration, Graph g, 
double *curr_page_rank_array, double *prev_page_rank_array, 
char ** array, double d);

#endif //GRAPH_H
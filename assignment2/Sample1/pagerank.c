// Zachary Ngooi Cheng Hong 
// z5228846 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "list.h"
#include "graph.h"
#include "string.h"
#define MAX_CHAR 1024
#define MAX_INVERTED 1000

int main (int argc, const char* argv[]) {
    assert(argc == 4);

    // Get number of urls from file
    int num_urls = count_urls_in_main_file();
    // Create array of urls
    char** array = array_creation(num_urls);
    // Maxmimum iterations.
    int max_iterations;
    // Damping Factor
    double damping;
    // Difference in PageRank sum.
    double wpr_diff;

    // Scan inputs
    sscanf(argv[1], "%lf", &damping);
    sscanf(argv[2], "%lf", &wpr_diff);
    sscanf(argv[3], "%d", &max_iterations);

    // Create graph
    Graph g = create_graph(num_urls);
    // Open each url
    open_file(array, num_urls, g);
    // Print out array for checking
    print_array(g, num_urls, array);
    // Calculate weighted page rank and output to file
    PageRankW(g, damping, wpr_diff, max_iterations, array);
    // Free memory for graph
    dropGraph(g);
    return 0;
}

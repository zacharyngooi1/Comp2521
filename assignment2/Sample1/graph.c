#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "list.h"
#include "graph.h"
#define MAX_INVERTED 1000
#define MAX_CHAR 1024

/////////////////////////////////////////////////////////
//                  Graph functions                    //
/////////////////////////////////////////////////////////

// Refrenced from https://webcms3.cse.unsw.edu.au/COMP2521/20T1/resources/41847
Graph create_graph(int num_of_vertices) {
    // Assert that number of verticies is valid
    assert (num_of_vertices >= 0);
    // First malloc required memory for struct
    Graph new_graph_struct = malloc(sizeof(struct graph_struct));
    // Now assert that the new graph is not NULL
    assert (new_graph_struct != NULL);
    // Set up struct of graph
    new_graph_struct->nV = num_of_vertices;
    new_graph_struct->nE = 0;
    // Allocate memory for the edges in the graph
    new_graph_struct->edges = malloc(num_of_vertices*(sizeof(double *)));
    // Assert edges are created
    assert(new_graph_struct->edges != NULL);
    // Iterate through the graph struct and create memory for row
    for (int counter = 0; counter < num_of_vertices; counter++) {              
        // Allocate memory for each row
        new_graph_struct->edges[counter] = calloc(num_of_vertices, sizeof(double));
        // Check if row does not have memory allocated
        assert(new_graph_struct->edges[counter] != NULL);
   }
    // Returns new graph
    return new_graph_struct;
}

// Print out array to check for positining
void print_array(Graph graph_struct, int number_of_urls, char **array) {
    for (int i = 0; i < number_of_urls; i++) {
        printf("%d--> %s| ", i, array[i]);
        for (int j = 0; j < number_of_urls; j++) {
            printf("%.0lf | ", graph_struct->edges[i][j]);
        }
        printf("\n");
    }
}

// free memory associated with graph, refrenced from LAB08 graph.c
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}


/////////////////////////////////////////////////////////
//                  file functions                     //
/////////////////////////////////////////////////////////

// Create function to open each url
void open_inner(char **array, int number_of_urls, Graph graph_struct, char *outer_url, int row) {
    char inner_urls[MAX_CHAR];
    FILE *fp = fopen(outer_url, "r");
    // We open each url inside 
    fgets(inner_urls, MAX_CHAR, fp);
    // Iterate through the url to get its list of connected urls
    while (fscanf(fp, "%s", inner_urls) == 1 && strcmp(inner_urls, "#end") != 0) {
        // Prevent self loops by checking if the connected url is the same as the curr array[row]
        if (strcmp(inner_urls, array[row]) == 0) {
            printf("Ignored self-loop: %s to %s\n", inner_urls, array[row]);
            continue;
        }
        printf("Reading file: %s\n", inner_urls);
        // Pass in the current name of the inner url and char array to find its relative postion in the row
        int col = find_position(array, inner_urls, number_of_urls);
        // Check that the col number is not -1
        assert (col != -99);
        // We must set the links to 1 to show the row has an outbound link to these columns
        graph_struct->edges[row][col] = 1;
    }
}

// Create a function to open the file to access its contents and connect neighbouring urls
void open_file(char** array, int number_of_urls, Graph graph_struct) {
    assert(graph_struct != NULL);
    // The urls inside each file does have  .txt even though they are txt files so we must take this into account
    // when allocating memory for the urls as we will be adding .txt to the ends of each outer url
    char outer_url[MAX_CHAR + strlen(".txt")];
    // We must first assign each row to be the name of the outer url through a for loop
    for (int row = 0; row < number_of_urls; row++) {
        // Concatenate the outer urls with the .txt next to them to allow them to be opened
        strcpy(outer_url, array[row]); strcat(outer_url, ".txt");
        // We open and create the array
        open_inner(array, number_of_urls,graph_struct, outer_url, row);
    }
}

// We create a function that returns the col number position for the filenames when the word is found
int find_position(char** array, char* find_word, int number_of_urls) {
    for (int col = 0; col < number_of_urls; col++) {
        // If the array column is of the same name as the word we are searching for, we return that number 
        if (strcmp(array[col], find_word) == 0) {
            return col;
        }
    }
    // If not found we return -99
    return -99;
}

// Create a function to iterate throught the array and return a filled list.
 Node list_insertion(double *curr_page_rank_array, int num_of_urls, char** array, 
 Graph graph_struct) {
    Node new_list = NULL;
    for (int row = 0; row < num_of_urls; row++) {
        // Calc outbound links for each url
        double outbound_link_txt = outbound(graph_struct, num_of_urls, row);
        // Create a new node to insert into empty list
        Node insert = new_node(curr_page_rank_array[row],
        outbound_link_txt, array[row]);
        // Inserting this node into the list in descending order.
        new_list = insert_node(insert, new_list);
    }
    return new_list;
 }

void print_to_file(double *curr_page_rank_array, int num_of_urls, char** array, Graph graph_struct) {
    // Create empty list
    // Create txt file to output WPR
    FILE *output_txt = fopen("pagerankList.txt", "w");
    // create a new list, create and insert each node
    Node new_list = list_insertion(curr_page_rank_array, num_of_urls, 
    array, graph_struct);
    // Print the list to the txt_file.
    print_list(new_list, output_txt);
    // Free all values in the list.
    fclose(output_txt);
    free_list(new_list);
}

/////////////////////////////////////////////////////////
//               Calculation functions                 //
/////////////////////////////////////////////////////////

// Count outbound links
double outbound(Graph graph_struct, int num_urls_in_collection, int row) {
    double counter = 0;
    for (int j=0; j< num_urls_in_collection; j++){
        if (graph_struct->edges[row][j] != 0) {
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
double inbound(Graph graph_struct, int num_urls_in_collection, int col) {
    double counter = 0;
    for (int j=0; j< num_urls_in_collection; j++){
        if (graph_struct->edges[j][col] == 1) {
            counter ++;
        }
    }
    if (counter == 0) {
        counter = 0.5;
    }
    return counter;
}

// Sum the total outbound links for refrenced given url in the graph.
double total_outbound(int given_url, Graph graph_struct) {
    double sum = 0;
    for (int i = 0; i < graph_struct->nV; i++) {
        if (graph_struct->edges[given_url][i] == 1) {
            // Call indiv function to calculate outbound and sum
            sum += outbound(graph_struct, graph_struct->nV, i);
        }
    }
        return sum;
}

// Sum the total inbound links for a refrenced url in the graph.
double total_inbound(int given_url, Graph graph_struct) {
    double sum = 0;
    for (int i = 0; i < graph_struct->nV; i++) {
        if (graph_struct->edges[given_url][i] == 1) {
            // Call indiv function to calculate inbound and sum
            sum += inbound(graph_struct, graph_struct->nV, i);
        }
    }
    return sum;
}

// Calculate weight out function
double calc_weight_out(int source, int destination, Graph graph_struct) {
    // Numerator is the outbound links only for the refrence outbound
    double numerator = outbound(graph_struct, graph_struct->nV, destination);
    // denom is the sum of all outbound links for the refrenced outbound 
    double denom = total_outbound(source, graph_struct);
    double w_out = numerator/denom;
    return w_out;
}

// Calculate weight in function
double calc_weight_in(int source, int destination, Graph graph_struct) {
    // Numerator is the outbound links only for the refrence inbound
    double numerator = inbound(graph_struct, graph_struct->nV, destination);
    // denom is the sum of all outbound links for the refrenced inbound
    double denom = total_inbound(source, graph_struct);
    double w_in = numerator/denom;
    return w_in;
}

// Create a function to calculate page rank
void PageRankW(Graph graph_struct, double d, double diff_in_pr, int max_iteration, char ** array) {
    // Create two arrays to hold values to be multipled and saved for each iteration
    double *curr_page_rank_array = malloc(graph_struct->nV * sizeof(double));
    double *prev_page_rank_array = malloc(graph_struct->nV * sizeof(double));
    // Set each value in the two arrays to be 1/num_of_urls
    for (int row = 0; row < graph_struct->nV; row++) {
        curr_page_rank_array[row] = prev_page_rank_array[row] = 1.0 / graph_struct->nV;
    }
    // Pass in values to calculate page rank
    calculate_wpr(diff_in_pr, max_iteration, graph_struct, 
    curr_page_rank_array, prev_page_rank_array, array, d);
    free(curr_page_rank_array);
    free(prev_page_rank_array);
}

// Calculate indiv weighted page rank  
void calculate_wpr(double diff_in_pr, int max_iteration, Graph graph_struct, 
double *curr_page_rank_array, double *prev_page_rank_array, 
char ** array, double d) {

    // As refrenced from spec sheet in assignment brief
    double diff = diff_in_pr;
    int iteration = 0;
    while (iteration < max_iteration && diff >= diff_in_pr) {
        diff = 0;
        for (int row = 0; row < graph_struct->nV; row++){
            double sum = 0;
            for (int inner_row = 0; inner_row < graph_struct->nV; inner_row++){
               if (graph_struct->edges[inner_row][row] != 0) {
                   sum += prev_page_rank_array[inner_row] 
                   * calc_weight_in(inner_row,row, graph_struct) 
                   * calc_weight_out(inner_row,row, graph_struct);
               }

            }
            // calc curr pagerank for that row
            curr_page_rank_array[row] = ((1.0 - d)/ graph_struct->nV) + d * sum;
        }
        // Calc diff sum
        for (int curr_row = 0; curr_row < graph_struct->nV; curr_row++){
        diff += fabs(curr_page_rank_array[curr_row] -
         prev_page_rank_array[curr_row]);

        // Set the prev array to be the curr array values for the next iteration
        prev_page_rank_array[curr_row] = curr_page_rank_array[curr_row];
        }
    iteration ++;
    }
    // call print function for curr page rank array and array of urls
    print_to_file(curr_page_rank_array, graph_struct->nV, array, graph_struct);
}
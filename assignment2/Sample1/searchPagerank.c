// Zachary Ngooi Cheng Hong 
// z5228846 
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"
#include "string.h"
#define MAX_CHAR 1024
#define MAX_INVERTED 1000

int main(int argc, char *argv[]) { 
    if (argc < 2) {
        printf("Invalid number of inputs\n");
        return 0; 
    }
    // Create a new empty list.
    inverted_Node new_list = NULL;
    // iterate through command line arguments
    for (int probe = 1; probe < argc; probe++){
        // malloc memory for each word after the 0 index and add null term
        char *search_word = malloc(strlen(argv[probe]) + 1);
        strcpy(search_word, argv[probe]);
        // Insert empty list and search word into function
        new_list = open_outer(new_list, search_word);
    }
    // Print the now sorted list
    print_inverted_list(new_list);
    free_inverted_list(new_list);
    return 0;
}
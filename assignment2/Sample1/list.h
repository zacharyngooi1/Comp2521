#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#define MAX_INVERTED 1000
#define MAX_CHAR 1024

// Create struct for linked list
struct linked_list {
    char *url_name;
    double page_rank;
    int outbound_links;
    struct linked_list *next;
};

typedef struct linked_list *Node;

// Create struct for linked list
struct inverted_linked_list {
    char *url;
    double page_rank_inverted;
    int search_count;
    struct inverted_linked_list *next;
};

typedef struct inverted_linked_list *inverted_Node;


//////////////////////////////
///     Node Functions     ///
//////////////////////////////

// Create new node for linked list in page rank.
Node new_node( double page_rank, int outbound_links, char* url_name);
// Create new node for linked list in search page rank.
inverted_Node new_inverted_node(double page_rank_inverted, char *url );

//////////////////////////////
///   Insertion Functions  ///
//////////////////////////////

// Inserts node into list in page rank.
Node insert_node(Node insert_node, Node new_list);
// Inserts node into list in search page rank.
inverted_Node insert_inverted(inverted_Node insert_node, inverted_Node new_list);

inverted_Node open_outer(inverted_Node new_list, char *search_word);

inverted_Node search_page(inverted_Node list, char *token);
//////////////////////////////
///    Sorting Functions   ///
//////////////////////////////

// Sorts list into descending order of page freq
void bubble_sort(inverted_Node list);
// Sorts ***already*** sorted list by page weight
void page_rank_sort(inverted_Node list);
// Swaps two nodes
void swap( inverted_Node a, inverted_Node b);

//////////////////////////////
///   Printing Functions   ///
//////////////////////////////

// Prints inverted list to terminal.
void print_inverted_list(inverted_Node list);
// Prints list to output file.
void print_list(Node list, FILE *output);

//////////////////////////////
///    Freeing Functions   ///
//////////////////////////////

// Frees inverted list for search page
void free_inverted_list(inverted_Node list);
// Frees weighted page rank list
void free_list(Node list);

#endif //LIST_H
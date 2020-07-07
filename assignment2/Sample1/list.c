#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "list.h"
#include "string.h"
#include "graph.h"
#define MAX_INVERTED 1000
#define MAX_CHAR 1024

//////////////////////////////
///     Node Functions     ///
//////////////////////////////

// Make a function to create a new node.
Node new_node(double page_rank,
int outbound_links, char* url_name) {
    // Malloc memory for new node
    Node new_node = malloc(sizeof(struct linked_list));
    // Check for memory allocation
    assert(new_node != NULL);
    // Assign values to new node
    new_node->outbound_links = outbound_links;
    // Allocate mem for url
    new_node->url_name = string_alloc(url_name);
    new_node->page_rank = page_rank;
    new_node->next = NULL;
    // Return node.
    return new_node;
}
// Create a function to create node for inverted.txt
inverted_Node new_inverted_node(double page_rank_inverted, char *url) {
    // Malloc memory for new node.
    inverted_Node new_node = malloc(sizeof(struct inverted_linked_list));
    // Check memory is allocated
    assert(new_node != NULL);
    // Set search count to be 1 as freq starts at 1
    new_node->search_count = 1;
    // Allocate mem for url
    new_node->url = string_alloc(url);
    new_node->page_rank_inverted = page_rank_inverted;
    new_node->next = NULL;
    // Return new node.
    return new_node;
}

//////////////////////////////
///   Insertion Functions  ///
//////////////////////////////

// Insert a given node in a list in descending order of WPR
Node insert_node(Node insert_node, Node new_list) {
    // If the list is currently empty.
    if (new_list == NULL) {
        return insert_node;
    }
    // Set curr to be head of the list
    Node curr = new_list;
    // Check if the PR for insertion node is more than the head of the list.
    if (insert_node->page_rank >= new_list->page_rank) {
        // Set insert node to be before curr.
        insert_node->next = curr;
        // Return new head of the list.
        return insert_node;
    }
    // Loop through list.
    while (curr->next != NULL) {
        // Check is insertion node is to be inserted between curr and curr->next.
        if (insert_node->page_rank >= curr->next->page_rank){
            insert_node->next = curr->next;
            curr->next = insert_node;
           // Return new head
            return new_list;
        }
        // Will run till tail of list is reached
        curr = curr->next;
    }
    // Node to be inserted is to be at the end of the list.
    curr->next = insert_node;
    return new_list;
}

// Create function to insert into list without duplication
inverted_Node insert_inverted(inverted_Node insert_node, inverted_Node new_list) {
    // Check if list is null
    if (new_list == NULL) {
        // Return new head of list.
        return insert_node;
    }
    // Set node for head of list.
    inverted_Node curr = new_list;
    while (curr->next != NULL) {
        // Check for duplications, if present, ignore node to be 
        // inserted and return list after incrementing curr search count.
        if (strcmp(curr->url, insert_node->url) == 0) {
            curr->search_count += 1;
            // Since we dont need the inserted node, 
            //we free the memory allocated to it
            free(insert_node->url);
            free(insert_node);
            return new_list;
        }
        curr = curr->next;
    }
    // Our function will not check for duplication  
    // atthe tail of the list so we muct check
    if (strcmp(curr->url, insert_node->url) == 0) {
        curr->search_count += 1;
        free(insert_node->url);
        free(insert_node);
        return new_list;
    }
    curr->next = insert_node;
    return new_list;
}

// Function to search inverted index.txt
inverted_Node open_outer(inverted_Node new_list, char *search_word) {
    char line[MAX_INVERTED];
    const char s[2] = " ";
    char *token;
    // Opens txt file
    FILE *index_file = fopen("invertedIndex.txt", "r");
    // Takes in each line of txt file
    while (fgets(line, sizeof line, index_file) != NULL){
        // tokenize each word separated by " "
        token = strtok(line, s);
        // Check if the tokenized word is the same as the word we want to find
        if (strcmp(token, search_word) == 0) {
            // Skip the first word as we only want to read in the urls.
            token = strtok(NULL, s);
            // Start looping through that line and stop before the null terminator
            while (token != NULL && strcmp(token, "\n") != 0) {
                // For each url attached to the search word, we will search for it in
                // the pagerank.txt 
                new_list = search_page(new_list, token);
                token = strtok(NULL, s);
            }
        }
    }
    fclose(index_file);
    return new_list;
}
// Function to search pageranklist
inverted_Node search_page(inverted_Node new_list, char *token) {
    // Open txt file containing weighted page rank
    FILE *weighted = fopen("pagerankList.txt", "r");
    double pg_rank;
    char temp2[MAX_INVERTED];
    char url[MAX_INVERTED];
    // iterate through each line for which has 3 diff values
    while (fscanf(weighted,"%s %s %lf", url, temp2, &pg_rank) == 3) {
        // Remove the "," from each url in the line before we compare it
        int length = strlen(url);
        url[length - 1] = '\0';
        // Check if the current url in pagerank.txt is equals our tokenized url
        if (strcmp(token, url) == 0) {
            // insert into linked list which wil automatically ignore duplicates
            inverted_Node insert_node = new_inverted_node(pg_rank, url);
            // insert into linked list which wil automatically ignore duplicates
            new_list = insert_inverted(insert_node, new_list);
            // If found, break as no duplicate urls are present in the pagerank.txt
            break;
        }

    }
    fclose(weighted);
    return new_list;
}

//////////////////////////////
///    Sorting Functions   ///
//////////////////////////////

// Refrenced from https://webcms3.cse.unsw.edu.au/COMP2521/20T1/resources/41893
// Sorting algortihms
void bubble_sort(inverted_Node list) 
{   assert(list != NULL);
    inverted_Node curr; 
    inverted_Node holder = NULL;
    int condition = 0; 
    // Run for the head of the list once before checking for condition 
    do {
        condition = 0; 
        // Set curr for head
        curr = list;
        // Whiile next of head is not equals to the holder
        while (curr->next != holder) {
            // Cheeck if the search freq of curr is less than the curr->next search
            if (curr->search_count <= curr->next->search_count) {
                // Swap curr and curr->next;
                swap(curr, curr->next);
                // Set condtion to be 1
                condition = 1;
            }
            curr = curr->next;
        }
        // Set holder to be one less of what it was for each iteration so the loop
        // Will run until the holder is at the start of the list and thus list is sorted
        holder = curr; 
    }
    while (condition == 1); 
} 

// Create a function to sort the bubble sorted list.
void page_rank_sort(inverted_Node list) { 
    // Since it is in descending order already
    assert(list != NULL);

    inverted_Node holder = NULL;

    int condition = 0;
    do {
        condition = 0;
        inverted_Node curr = list;

        while (curr->next != holder) {
            // if it is equal, we must swap the curr and curr->next
            if (curr->page_rank_inverted <= curr->next->page_rank_inverted &&
            curr->search_count == curr->next->search_count) {
                swap(curr, curr->next);
                condition = 1;
            }
            // If not we increment till we find a match in search counts
            curr = curr->next;
        }
        holder = curr; 
    }
    while (condition == 1);
} 

//function to swap data of two nodes
void swap(inverted_Node curr, inverted_Node next) 
{ 
    assert(curr != NULL);
    assert(next != NULL);
    // Create temps to hold the curr values
    int temp = curr->search_count;
    char *temp2 = curr->url;
    double temp3 = curr->page_rank_inverted;
    curr->url = next->url;
    curr->page_rank_inverted = next->page_rank_inverted;
    curr->search_count = next->search_count;
    // Set next to temp values
    next->url = temp2; 
    next->page_rank_inverted = temp3;
    next->search_count = temp; 
} 

//////////////////////////////
///   Printing Functions   ///
//////////////////////////////

// Create function to print list.
void print_inverted_list(inverted_Node list) {
    // Check that list is not null.
    assert(list != NULL);
    // First we sort the list in descending order of freq
    bubble_sort(list);
    // Since the list is now sorted, we can sort each freq by page weight
    page_rank_sort(list);
    // Create counter
    int counter = 0;
    // Print out list
    while (list != NULL) {
        if (counter <= 30) {
            printf("%s\n", list->url);
            //printf("%lf %d\n", list->page_rank_inverted, list->search_count);
        }
        counter ++;
        list = list->next;
    }
}

// Create a function to print the list to the output file
void print_list(Node list, FILE *output) {
    assert(list != NULL);
    while (list != NULL) {
        fprintf(output, "%s, %d, %.7lf\n", list->url_name, 
        list->outbound_links, list->page_rank);
        list = list->next;
    }
}

//////////////////////////////
///    Freeing Functions   ///
//////////////////////////////

// Create function to free list from memory.
void free_list(Node list) {
    // Create temp node t.
    Node curr = NULL;
    while (list != NULL) {
        // set curr and iterate to next in list.
        curr = list;
        list = list->next;
        // Free memory.
        free(curr->url_name);
        free(curr);
    }
}

// Create function to free list.
void free_inverted_list(inverted_Node list) {
   inverted_Node curr = NULL;
   while (list != NULL) {
       curr = list;
       list = list->next;
       // Free as we go through the list.
       free(curr->url);
       free(curr);
    }
}
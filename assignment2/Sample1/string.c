#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "string.h"
#define MAX_CHAR 1024
#define MAX_INVERTED 1000


// Get the number of urls(vertices) in the main collection file
int count_urls_in_main_file() {
    FILE *fp = fopen("collection.txt", "r");
    char buffer[MAX_CHAR];
    int count = 0;
 
    while (fscanf(fp, "%s", buffer) != EOF) {
        count++;
    }
 
    fclose(fp);
    return count;
}

// Malloc memory for string.
char *string_alloc(const char* word_to_dupe) {
    // Include length of string plust plus 1 for null term.
    char *str = malloc(strlen(word_to_dupe) + 1);
    // check mem is allocated
    assert(str != NULL);
    strcpy(str, word_to_dupe);
    return str;
}


// Create an array of strings of all urls in collection.
char** array_creation(int num_urls) {
    char** array = malloc(num_urls * sizeof(char*));
    // Open collection file.
    FILE *fp = fopen("collection.txt", "r");
    char url[MAX_CHAR];
    int i = 0;
    // Store each url in array.
    while (fscanf(fp, "%s", url) == 1) {
        array[i] = string_alloc(url);
        i++;
    }
    fclose(fp);
    return array;
}

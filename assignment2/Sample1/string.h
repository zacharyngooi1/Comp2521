#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#define MAX_CHAR 1024
#define MAX_INVERTED 1000

// Counts number of urls in file
int count_urls_in_main_file();
// Allocates memory for a string
char *string_alloc(const char* word_to_dupe);
// Creates an array to store url names
char** array_creation(int num_urls);

#endif // STRING_H

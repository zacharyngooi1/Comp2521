// mergeOrdered.c ... implementation of mergeOrdered function
// z5228846 -Zachary Ngooi
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* 
    You will submit only this one file.

    Implement the function "mergeOrdered" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/
List insertion_after(Node *s_list, Node *f_list, List empty_list);
List insert( List l, Node *node);

List mergeOrdered(List list1, List list2) {
   // assert both are not null
    if (list1 == NULL && list2 == NULL) {
        return NULL;
    }
    // Base case
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
     // Create a new list
    List empty_list = newList();
    // Set a value to be inserted
    int insertion_value;
    // Now we create 2 pointers to go through both lists at the same time
    Node *f_list = list1->first;
    Node *s_list = list2->first;
    // run while both lists are not null
    while (f_list != NULL && s_list != NULL) {
        // Check if the first list value is less than the
        // second list value
        if (f_list->value <= s_list->value) {
            // Save the value to be inserted
            insertion_value = f_list->value;
            // Go to next value in first list
            f_list = f_list->next;
        }
        // If the second pointer has a smaller value than the
        // first pointer, insert it instead.
        else {
            insertion_value = s_list->value;
            s_list = s_list->next;
        }
        // Create a node with the insertion value
        Node *insertion = newNode(insertion_value);
        // Insert into the list
        empty_list = insert(empty_list, insertion);
    }
    // insert the remaining values of either list 
    // if one list is null
    empty_list =  insertion_after(s_list, f_list, empty_list);
    return empty_list;
}

// insert the remaining values of either list 
// if one list is null
List insertion_after(Node *s_list, Node *f_list, List empty_list) {
    while (s_list != NULL) {
        Node *insertion = newNode(s_list->value);
        empty_list = insert(empty_list,insertion);
        s_list = s_list->next;
    }
    while (f_list != NULL) {
        Node *insertion = newNode(f_list->value);
        empty_list = insert(empty_list,insertion);
        f_list = f_list->next;
    }
    return empty_list;
}

// Insert function
List insert( List l, Node *node){
    // Base case if list is null
    if (l->first == NULL) {
        l->first = node;
        l->last = node;
        return l;
    }
    // Insert new node at the end of the list
    l->last->next = node;
    l->last = node;
	return l;
}


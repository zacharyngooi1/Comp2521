#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// User functions
List insert_file(List empty_list, Node insertion);
int calculate_abs(int x, int y);

List listGetAbnormals(List l, int threshold) {
	// Create a new list to insert into.
	List empty_list = newList();
	// Create a pointer to the first node in the list.
	Node curr = l->first;
	while (curr != NULL) {
		// If the curr is either first or last, it will never be abnormal.
		if ((curr == l->first) || (curr == l->last)){
			// go to the next node in the list.
			curr = curr->next;
		}
		else 
		{
			// Find the absolute differences.
			int diff1 = calculate_abs(curr->value, curr->prev->value);
			int diff2 = calculate_abs(curr->value, curr->next->value);
			// Check if the condition is fulfilled.
			if ((diff1 >= threshold) && (diff2 >= threshold)) {
				// Create a new node to be inserted into the empty list.
				Node insertion = newNode(curr->value);
				// insert into the list.
				empty_list = insert_file(empty_list, insertion);
			}
		// iterate to next node.
		curr = curr->next;
		}
	}
	// Return now filled/unfilled list
	return empty_list;
}

int calculate_abs(int x, int y){
	int ans = x - y;
	// absolute the answer
	ans = abs(ans);
	// return it
	return ans;
}

// Insertion function
List insert_file(List empty_list, Node insertion){
	// If the list contains nothing, size will be 0 
	if (empty_list->size == 0){
		// Set first and last pointers
		empty_list->last = empty_list->first = insertion;
		// Increase the size of the list by 1
		empty_list->size++;
		// Return the list
		return empty_list;
	}
	// Set pointer to the first element of the list.
	Node curr = empty_list->first;
	// Find the tail of the list.
	while (curr->next != NULL){
		curr = curr->next;
	}
	// Insert the node into the tail of the list	
	curr->next = insertion;
	// Point the inserted nodes prev pointer to the curr
	insertion->prev = curr;
	// Increase size of list by 1
	empty_list->size ++;
	// Set last pointer as the insertion node
	empty_list->last = insertion;
	// Return node.
	return empty_list;
}
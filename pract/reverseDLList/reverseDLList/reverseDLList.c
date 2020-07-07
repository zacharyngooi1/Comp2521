
#include "list.h"

void reverseDLList(List l) {
	if (l == NULL){
		return;
	}

	Node curr = l->first;
	Node previous = NULL;
	l->last = curr;
	while (curr != NULL) {
		previous = curr->prev;
		curr->prev = curr->next;
		curr->next = previous;
		curr = curr->prev; 
	}
	if (previous != NULL){
		previous = previous->prev;
		l->first = previous;
	}
}


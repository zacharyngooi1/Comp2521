
#include "list.h"

bool listIsOrdered(List l) {
	if (l == NULL || l->head == NULL){
	return true;
	}
	Node curr = l->head;
	if (curr->next == NULL){
		return true;
	}

	if  (curr->value >= curr->next->value){
		// This means its descending
		while (curr->next != NULL){
			if (curr->value < curr->next->value) {
					return false;
				}
			curr = curr->next;
		}
	}
	curr = l->head;
	if (curr->value <= curr->next->value) {
		while (curr->next != NULL) {
			if (curr->value > curr->next->value){
				return false;
			}
			curr = curr->next;
		}
	}
		return true;
}


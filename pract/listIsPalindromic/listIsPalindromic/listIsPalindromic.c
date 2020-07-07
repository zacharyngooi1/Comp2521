
#include "list.h"

bool listIsPalindromic(List l) {
	if (l == NULL) {
		return false;
	}
	Node front = l->first;
	Node back = l->last;
	while (front != back){
		if (front->value != back->value){
			return false;
		}
		front = front->next;
		back = back->prev;

	}	
	return true;
}


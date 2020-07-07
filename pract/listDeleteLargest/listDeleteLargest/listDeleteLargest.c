
#include "list.h"
int listDeleteLargest(List l) {
	int deleted = 0;
	int largest = 0;
	Node curr = l->head;
	while (curr != NULL){
		if (curr->value >= largest){
			largest = curr->value;
		}
		curr = curr->next;
	}
	curr = l->head;
	if (curr->value == largest && curr == l->head){
		deleted = largest;
		l->head->value = curr->next->value;
		l->head = curr->next;
		free(curr);
	}
	else{
		curr = l->head;
		Node prev = NULL;
		while (curr != NULL){
			prev = curr;
			curr = curr->next;
			if (curr->value == largest){
				deleted = largest;
				prev->next = curr->next;
				free(curr);
				break;
			}
		}
	}
	return deleted;
}

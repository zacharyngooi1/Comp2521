
#include "list.h"

int numDupesInOrderedList(List l) {
	if (l == NULL || l->head == NULL) {
		return 0;
	}
	int dupe_counter = 0;

	Node curr = l->head;
	while (curr != NULL) {
		Node curr1 = curr->next;
			while (curr1 != NULL) {
				if (curr->value ==curr1->value) {
					dupe_counter ++;
					break;
				}
				curr1 = curr1->next;
			}
		curr = curr->next;
	}
	return dupe_counter;
}


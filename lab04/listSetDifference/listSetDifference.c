
#include "list.h"

List listSetDifference(List l1, List l2) {
	// TODO
	// Create new insertion list.
	List insertion_list = newList();
	// Run through while loops
	struct node *l1curr = l1->head;

    while (l1curr != NULL) {
        struct node  *l2curr = l2->head;
        int checker = 0;
        while (l2curr != NULL) {
            if (l1curr->value == l2curr->value) {
                checker = 1;
            }
            l2curr = l2curr->next;
        }
        
        if (checker == 0) {
            if (insertion_list->head == NULL) {
                Node node_insert = newNode(l1curr->value);
                insertion_list->head = node_insert;
            }
            else {
                Node node_insertion_nonhead = newNode(l1curr->value);
                struct node *inner_curr = insertion_list->head;
                while (inner_curr->next != NULL) {
                    inner_curr = inner_curr->next;
                }
                inner_curr->next = node_insertion_nonhead;
            }
        }
        
        l1curr = l1curr->next;
    }
	
	return insertion_list;
}


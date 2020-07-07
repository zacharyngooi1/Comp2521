
#include "list.h"
List insertme( List l, Node node);

List listSetDifference(List l1, List l2) {
	List empty = NULL;
	empty = newList();
	Node curr = l1->head;
	Node curr_inner = l2->head;
	int flag = 0;

	while (curr != NULL) {
		flag = 0;
        curr_inner = l2->head;
		while (curr_inner != NULL) {
			if (curr->value == curr_inner->value) {
				flag = 1;
			}
			curr_inner = curr_inner -> next;	
		}
		if (flag == 0) {
			Node insert = newNode(curr->value);
			empty = insertme(empty, insert);
			// insert that value into empty list
		}
		curr = curr->next;
	}
	return empty;
}
List insertme( List l, Node node){
    node->next = l->head;
    l->head = node;

	return l;

}

#include "list.h"

List insert(List newList, Node node_to_insert);


List listSetIntersection(List s1, List s2) {
	if (s1 == NULL || s2 == NULL) {
		return NULL;
	}

	List newListnew = NULL;
	newListnew = newList();
	Node outercurr = s1->head;
	Node inner = s2->head;
	while (outercurr != NULL){
		while (inner != NULL){
			if (outercurr->value == inner->value){
				Node node_to_insert  = newNode(inner->value);
				newListnew = insert(newListnew, node_to_insert);
				break;
			}
			inner = inner->next;

		}
		outercurr = outercurr->next;
	}
	
	return newListnew;
}



List insert(List newlist, Node node_to_insert){
	if (newlist == NULL){
		newlist->head = node_to_insert;
		node_to_insert->next = NULL;
	}
	
	while (newlist->head->next!= NULL){
		newlist->head = newlist->head->next;

	}

	newlist->head->next = node_to_insert;

	return newlist;
}


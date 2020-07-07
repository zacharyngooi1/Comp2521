
#include "list.h"
List insertion(List empty_list, Node created);
int checker(List empty_list, Node created);

List listSetUnion(List s1, List s2) {
	List empty = newList();
    Node list2 = s2->head;
    Node list1 = s1->head;
    while (list1 != NULL) {
        Node creation = newNode(list1->value);
        creation->next = empty->head;
        empty->head = creation;
        list1 = list1->next;
    }

    while (list2 != NULL) {
        // Check if elemetn is present in list brefore inserting
        Node creation = newNode(list2->value);
       if (checker(empty,creation) != 1) {
        creation->next = empty->head;
        empty->head = creation;
       }
        list2 = list2->next;
    }
    
	return empty;
}
int checker(List empty_list, Node created) {
    Node curr = empty_list->head;
    int result = 0;
    while (curr != NULL) {
        if (curr->value == created->value) {
            result = 1;
            break;
        }
        curr = curr->next;
    }
    return result;
}



#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	if (t == NULL){
		return 0;
	}

	if (key < t->value){
		return BSTreeNodeDepth(t->left, key) + 1;
	}
	else if (key > t->value){
		return BSTreeNodeDepth(t->right, key) + 1;
	}
	else if (key == t->value) {
		return 0;
	}
	else {
		return -1;
	}
	
	
	return -1;
}


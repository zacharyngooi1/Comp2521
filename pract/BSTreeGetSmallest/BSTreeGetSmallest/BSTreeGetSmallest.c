
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return NULL;
	}
	if (t->left == NULL){
		return t;
	}

	if (t->left != NULL){
		return BSTreeGetSmallest(t->left);
	}

	return NULL;
}


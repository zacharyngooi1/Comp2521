
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	// Base case
	if (t == NULL){
		BSTree node = malloc(sizeof(struct BSTNode));
		node->value = val;
		node->right = NULL;
		node->left = NULL;
		return node;
	}
	else {
		if (val < t->value) {
			t->left = BSTreeInsert(t->left, val);
		}
		if (val > t->value) {
			t->right = BSTreeInsert(t->right, val);
		}
		if (val == t->value){
			return NULL;
		}
	}
	return t;

}


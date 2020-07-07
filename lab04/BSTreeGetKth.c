#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int counter(BSTree t);

int BSTreeGetKth(BSTree t, int integer) {
	int num = counter(t->left);

	if (integer < num) {
		return BSTreeGetKth(t->left, integer);
	} else if (integer > num) {
		return BSTreeGetKth(t->right, integer - num - 1);
	} else {
		return t->value;
	}
}

int counter(BSTree t) {
	int x = 1;
	if (t == NULL) {
		return 0;
	} else {
		x += counter(t->left);
		x += counter(t->right);
		return x;
	}
}

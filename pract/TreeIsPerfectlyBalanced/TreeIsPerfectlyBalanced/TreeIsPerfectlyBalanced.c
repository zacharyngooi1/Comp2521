
#include <stdlib.h>

#include "tree.h"
int height(Tree t);

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	}

	int a = height(t->left);
	int b = height(t->right);
	if (abs(a-b +1) > 1) {
		return false;
	}
	
	return true;
}


int height(Tree t){
	// find number of nodes on left and right
	if (t == NULL){
		return 0;
	}
	else {
		
		return height(t->left)+ height(t->right) +1;

	}
		
}

#include <stdlib.h>

#include "tree.h"


int getHeight(Tree node);

int nodeNum(Tree node) {
    
    if (node == NULL) {
        return 0;
    }
    
    else {
        return nodeNum(node->left) + nodeNum(node->right) + 1;
    }
}

bool TreeIsPerfectlyBalanced(Tree t) {

    if (t == NULL) {
        return true;
    }
	
    int leftcount = nodeNum(t->left);  
    
    int rightcount = nodeNum(t->right);
    
    if (abs(leftcount-rightcount) <= 1 && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right)) {
        return true;
    }
    
    else {
    	return false;
    }
}


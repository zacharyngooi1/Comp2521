
#include <stdio.h>

#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	 if (t == NULL) 
        return; 
  
     // first recur on left subtree 
     BSTreePostfix(t->left); 
  
     // then recur on right subtree 
     BSTreePostfix(t->right); 
  
     // now deal with the t 
     printf("%d ", t->value);
}



#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    int ans = 0;
    if (t == NULL)
    return -1;
    else {
        int a = TreeHeight(t->left);
        int b = TreeHeight(t->right);
        if (a > b){
            ans = a+1;
            return ans;
        }
        else{
            ans = b+1;
            return ans;
        }
    }

}



#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {

	if (t == NULL){
		return 0;
	}
    int sum = 0;

    if (t->value % 2 != 0) {
        sum += t->value;
    }
    return sum + TreeSumOdds(t->left) + TreeSumOdds(t->right);
}


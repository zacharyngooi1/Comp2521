
#include <stdlib.h>

#include "BSTree.h"
#include <stdio.h>

int ans = 0;
void fun(BSTree t, int k, int *idx){
    if(!t) return;
    fun(t->left, k, idx);
    if (*idx == k) ans = t->value;
    (*idx)++;
    fun(t->right, k, idx);
}

int BSTreeGetKth(BSTree t, int k) {
    int idx = 0;
    fun(t, k, &idx);
    return ans;
}


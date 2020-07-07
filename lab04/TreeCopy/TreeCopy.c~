#include "tree.h"

Tree newTree(int integer);

Tree TreeCopy(Tree t, int height) {
	if (height < 0 || t == NULL)
	{
		return NULL;
	}

	Tree x = newTree(t->value);
	x->left = TreeCopy(t->left, height - 1);
	x->right = TreeCopy(t->right, height - 1);

	return x;
}

Tree newTree(int integer) {
	Tree new = malloc(sizeof(struct node));
	new->value = integer;
	new->left = NULL;
	new->right = NULL;

	return new;
}




#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// User functions.
BSTree delete_me(BSTree node);
BSTree joiner(BSTree left, BSTree right);
BSTree get_parent(BSTree t);
BSTree get_min(BSTree t);

BSTree BSTreeTrim(BSTree t, int lower, int upper) {
	if (t == NULL) {
		return t;
	}
	// Call right of root.
	t->right = BSTreeTrim(t->right, lower, upper);
	// Call left of root.
	t->left = BSTreeTrim(t->left, lower, upper);
	
	// Check if value of root is within range.
	if ((t->value >= lower) && (t->value <= upper)) {
		// Delete root and join its children if needed.
		return delete_me(t);
	}

	return t;
}

BSTree delete_me(BSTree t) {
	// Base case 1
	// If left is null, only need to return the right child
	if (t->left == NULL) {
		BSTree right_child = t->right;
		free(t);
		return right_child;
	} 
	// Base case 2
	// If right is null, only need to return the left child
	if (t->right == NULL) {
		BSTree left_child = t->left;
		free(t);
		return left_child;
	}
	// Create a temp to hold both the left and right subtrees after
	// They are joined together
	BSTree holder = joiner(t->left, t->right);
	// kill t
	free(t);
	// make root the holder
	t = holder;

	return t;
}

BSTree joiner(BSTree left_sub, BSTree right_sub) {
	// We need to join both left subs and right subs
	BSTree holder_right = right_sub;
	// Get parent of lowest value in holder
	BSTree parent = get_parent(holder_right);
	// Now my holder_right is the lowest value in my right subtree
	holder_right = get_min(holder_right);
	// If parent not null anything on the right of my min
	// must be elevated to the left of parent
	if (parent != NULL) {
		parent->left = holder_right->right;
		// Now minimum is my new root node and connect to right_sub
		holder_right->right = right_sub;
	}
	// root node's left is my left subtree
	holder_right->left = left_sub;
	// return my root node
	return holder_right;
}

// Gets parent node of left sub
BSTree get_parent(BSTree t){
	if (t ==NULL){
		return NULL;
	}
	BSTree parent = NULL;
	while (t->left != NULL){
		parent = t;
		t = t->left;
	}
	return parent;
}

// Gets min of tree
BSTree get_min(BSTree t) {
	if (t ==NULL){
		return NULL;
	}	
	while (t->left != NULL){
		t = t->left;
	}
	return t;
}

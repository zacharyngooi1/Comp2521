// equalBST.c ... implementation of equalBST function
// z5228846 -Zachary Ngooi
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "equalBST" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

int equalBST(BSTree t1, BSTree t2) {
	// Base case check if both trees are NULL
    int result = 0;
    if (t1==NULL && t2==NULL) {
        result = 1;
        return result;
    }
    // If both are not null
    if (t1!=NULL && t2!=NULL) { 
        // Check if keys are the same and call both left and right
        // subtrees recursively
        if (t1->key == t2->key && equalBST(t1->left, t2->left) 
        && equalBST(t1->right, t2->right)) {
            // Set result to be 1
            result = 1;
            return result;
        }
    } 
    // Return result = 0 if nothing is satisfied.
    return result; 
}


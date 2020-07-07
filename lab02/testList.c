// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

int main (void)
{
	DLList myList = getDLList (stdin);
	assert (validDLList (myList));
	

	// Before function: adding first item before the current.
	printf("\n\n-------------TEST 1-------------\n\n");
	printf("State of the list before operation: \n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Adding a node to the start of the list using the before function......\n");
	DLListBefore(myList, "New line before the beginning");
	printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	// Before function: adding in the middle before the current.
	printf("\n\n-------------TEST 2-------------\n\n");
	printf("List before operation:\n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Adding a node in the middle of the list using the before function");
	printf(" function......\n");
	DLListMove(myList,1);
	DLListBefore(myList, "New line in the middle for the before funtion");
	printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));


	// After function: adding as the last items after the current.
	printf("\n\n-------------TEST 3-------------\n\n");
	printf("State of the list before operation: \n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Adding a item at the end of the list......\n");
	DLListMove(myList, 9999);
	DLListAfter(myList, "New line at the end");
	printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	// After function: adding in the middle after the current.
	printf("\n\n-------------TEST 4-------------\n\n");
	printf("State of the list before operation: \n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Adding a item in the middle after curr......\n");
	DLListMove(myList, -1);
	DLListAfter(myList, "New line in the middle for after function");
    printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	// Delete function: delete first item
	printf("\n\n-------------TEST 5-------------\n\n");
	printf("State of the list before operation: \n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Deleting the first item in the list......\n");
	DLListMove(myList, -9999);
	DLListDelete(myList);
    printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	// Delete function: delete last item
	printf("\n\n-------------TEST 6-------------\n\n");
	printf("State of the list before operation\n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Deleting the last item in the list......\n");
	DLListMove(myList, 9999);
	DLListDelete(myList);
	printf("State of the list after the operation: \n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	// Delete function: delete item in the middle
	printf("\n\n-------------TEST 7-------------\n\n");
	printf("State of the list before operation: \n\n");
	putDLList(stdout, myList);
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));
	printf("Deleting a middle item in the list......\n");
	DLListMove(myList, -1);
	DLListDelete(myList);
	DLListDelete(myList);
	DLListDelete(myList);
	DLListDelete(myList);
	DLListDelete(myList);
	DLListDelete(myList);
    printf("State of the list after the operation: \n\n");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\nThe value of curr is: (%s)\n", DLListCurrent(myList));
	printf("The value of nitems is: (%zu)\n", DLListLength(myList));

	
	freeDLList (myList);
	return EXIT_SUCCESS;
}

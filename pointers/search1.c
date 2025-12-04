#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARGS 100

int items[MAXARGS];
int numItems = 0;

//traditional way of searching for a value in an array
int search1(int value) {
	for(int i=0; i<numItems; i++)
		if (value == items[i]) //address of items + i * 4
			return i;
	return -1;
}

//searching using pointers - return index!
int search2(int value) {
	int *itemp = items;
	while (value != *itemp) {
		itemp++;
		if (!*itemp) // if (*itemp == 0)
			return -1;
	}
	return itemp - items; //compute index!
}

//search using pointers - return pointer!
int *search3(int value) {
	int *itemp = items; // &items[0]
	while (value != *itemp) {
		itemp++;
		if (!*itemp)
			return NULL;
	}
	return itemp;
}

int main(int argc, char *argv[]) {
	//process command line args - convert to int and store in array
	numItems = argc-1;
	for(int i=1; i<argc; i++)
		items[i-1] = atoi(argv[i]);
	items[numItems] = 0; //indication for end of array

	printf("Enter a number: ");
	int input = 0;
	scanf("%d", &input);

	printf("%d found at index %d\n", input, search1(input));
	printf("%d found at index %d\n", input, search2(input));
	printf("%d found at address %x\n", input, search3(input));
}

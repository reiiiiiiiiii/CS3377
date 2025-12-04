#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

	int array[10];
	int n = atoi(argv[1]);
	printf("0x%x 0x%x 0x%x\n", array, &n, argv[1]);

	for(int i=0; i<n ; i++)
		array[i] = i;

	for(int i=0; i<n ; i++)
		printf("%d ", array[i]);
	putchar('\n');
}

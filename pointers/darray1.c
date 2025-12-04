#include <stdio.h>
#include <stdlib.h>

double array[10];

int main(int argc, char *argv[]) {

	int n = atoi(argv[1]);
	printf("0x%x 0x%x 0x%x\n", array, &n, argv[1]);

	for(int i=0; i<n ; i++)
		array[i] = i;

	for(int i=0; i<n ; i++)
		printf("%.0lf ", array[i]);
	putchar('\n');
}

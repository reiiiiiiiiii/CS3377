#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	long n = atoi(argv[1]);
	int array[n];
	printf("%ld %x\n", n, array);

	for(long i=0; i<n ; i++)
		array[i] = i;

	for(long i=0; i<n ; i++)
		array[i]++;

	putchar('\n');
}

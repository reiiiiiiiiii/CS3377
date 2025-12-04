#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	long n = atol(argv[1]);
	int *array = (int *) malloc( n * sizeof(int) );
	printf("%ld %x\n", n, array);

	for(long i=0; i<n ; i++)
		array[i] = i;

	for(long i=0; i<n ; i++)
		array[i]++;
}

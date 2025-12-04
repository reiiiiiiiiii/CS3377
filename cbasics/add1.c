#include <stdio.h>
#include <stdlib.h>

// Usage: add1 <num1> <num2> [num3 ...]
int main(int argc, char *argv[]) {
	int total = 0;

	for(int i = 1; i < argc; i++) {
		total += atoi(argv[i]);	
	}
	printf("Total: %d\n", total);
}

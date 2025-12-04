#include <stdio.h>

int s[100];

int main() {
	printf("int: %d bytes\n", sizeof(int));
	printf("float: %d bytes\n", sizeof(float));
	printf("double: %d bytes\n", sizeof(double));
	printf("char: %d bytes\n\n", sizeof(char));
	printf("int *: %d bytes\n", sizeof(int *));
	printf("float *: %d bytes\n", sizeof(float *));
	printf("double *: %d bytes\n", sizeof(double *));
	printf("char *: %d bytes\n", sizeof(char *));
	printf("void *: %d bytes\n", sizeof(void *));
}

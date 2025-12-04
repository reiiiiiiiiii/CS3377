#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int i;
	for(i=1; i<100; i++)
		if (!fork()) 
			break;

	for(int j=1; j<100; j++)
		wait(NULL);

	printf("%3d * %2d = %5d\n", n, i, n*i);
}

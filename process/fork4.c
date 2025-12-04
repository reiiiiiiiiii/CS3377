#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	//parent should create exactly n children
	for(int i=0; i<n; i++)
		if (!fork()) // (fork() == 0) is this child process?
			break;

	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());

	//waiting for children mode!
	for(int i=0; i<n; i++)
		wait(NULL);
}

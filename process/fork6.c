#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]); 
	//binary tree with max depth n
	for(int i=0; i<n; i++)
		if (fork()) //parent goes down, child goes up to for loop
			if (fork()) //parent goes down, child goes up to for loop
				break;
	// if (fork() && fork()) will this work similiarly?
	// break;                short circuiting when evaluating expressions
	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
	wait(NULL);
	wait(NULL);
}

#include <stdio.h>
#include <unistd.h>

int main() {
	//fork() returns 0 for new process (child), returns child's pid for the parent
	if (fork()) 
		printf("I am the parent! Hello from %d! My parent is %d.\n", getpid(), getppid());
	else
		printf("I am the child! Hello from %d! My parent is %d.\n", getpid(), getppid());
}

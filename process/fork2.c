#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	fork();
	fork();
	printf("Hello from %d! My parent is %d.\n", getpid(), getppid());
	wait(NULL);
	wait(NULL);
}

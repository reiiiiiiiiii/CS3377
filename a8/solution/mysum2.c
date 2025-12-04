#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//2 pipes to send data to child, 1 pipe to read the result
//index 0 and 1                  index 2
#define MAXPIPES 3

int fds[MAXPIPES][2]; 

void child() {
	puts("Getting child ready for hard work...");
	//rewire the pipes and invoke the program "add"
	//rewire first pipe read to fd 0
	dup2(fds[0][0], 0); //equivalent to close(0); dup(fds[0][0]); 
	//rewire second pipe read to fd 3
	dup2(fds[1][0], 3); //equivalent to close(3); dup(fds[1][0]);
	//rewire third pipe write to fd 1
	dup2(fds[2][1], 1); //equivalent to close(1); dup(fds[2][1]);

	execl("./add", "add", "-v", NULL);  //any argument will enable debug messages
	//execl("./add", "add", NULL);
	fprintf(stderr, "world is ending!\n"); //use stderr since stdout has been already redirected
}

void doNothing() {
	while (1)
		sleep(1);
}

int main() {
	//since fd 3 is used by add, ... etc, make it busy so that it won't be used by pipes
	printf("Reserving fd %d for future use.\n", dup(0)); 

	//pipe fd values (3,4), (5,6), (7,8) --> (4,5), (6,7), (8,9)
	for(int i=0; i<MAXPIPES; i++)
		pipe(fds[i]);

	if (!fork())
		child();

	if (!fork())
		doNothing();
	
	//read the data from the user and pump them to pipes
	int x, y, z;
	printf("Enter 2 numbers:\n");
	while (scanf("%d%d", &x, &y) == 2) {
		//write x and y to pipes --> child process
		write(fds[0][1], &x, sizeof(int));	
		write(fds[1][1], &y, sizeof(int));	
		//read result from pipe <-- sent by child 
		read(fds[2][0], &z, sizeof(int));
		printf("result: %d\n", z);
	}
	//read the output and print...
}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000

int main() {
	int fds[2] = {};
	pipe(fds);
	printf("read: %d, write: %d\n", fds[0], fds[1]);

	if (fork()) { //parent process
		//get a line from the user
		char buffer[MAXLEN];
		printf("Parent - Enter line: ");
		fgets(buffer, MAXLEN, stdin);
	
		//now, write to pipe, then try to read from pipe
		write(fds[1], buffer, strlen(buffer)+1);
	} else { //child process 
		char readBuffer[MAXLEN];
		puts("child");
		if (read(fds[0], readBuffer, MAXLEN) > 0)
			printf("Child read from pipe: %s\n", readBuffer);
		else
			puts("Pipe read error!\n");
	}
}

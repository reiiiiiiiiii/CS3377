#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000

int main() {
	int fds[2] = {0, 0};
	pipe(fds);
	printf("read: %d, write: %d\n", fds[0], fds[1]);

	//get a line from the user
	char buffer[MAXLEN];
	printf("Enter line: ");
	fgets(buffer, MAXLEN, stdin);
	
	//now, write to pipe, then try to read from pipe
	write(fds[1], buffer, strlen(buffer)+1);
	char readBuffer[MAXLEN];
	read(fds[0], readBuffer, MAXLEN);
	printf("Read from pipe: %s\n", readBuffer);
}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1000

int main() {
	int tochild[2] = {}, toparent[2] = {};
	pipe(tochild);
	pipe(toparent);
	printf("tochild:  read: %d, write: %d\n", tochild[0], tochild[1]);
	printf("toparent: read: %d, write: %d\n", toparent[0], toparent[1]);

	if (fork()) { //parent process
		close(tochild[0]); //cleanup can help in debugging huge programs
		close(toparent[1]);

		//get a line from the user
		char buffer[MAXLEN];
		puts("Parent - Enter line: ");
		fgets(buffer, MAXLEN, stdin);
	
		//now, write that line to child
		write(tochild[1], buffer, strlen(buffer)+1);
		//wait & read the response from the child
		read(toparent[0], buffer, MAXLEN);
		printf("Child returned: %s\n", buffer);
	} else { //child process 
		close(tochild[1]); //cleanup can help in debugging huge programs
		close(toparent[0]);
	
		puts("child is ready");

		char readBuffer[MAXLEN];
		//read the message from the parent
		read(tochild[0], readBuffer, MAXLEN);

		//do some processing
		for(int i=0; i<strlen(readBuffer); i++) {
			readBuffer[i] = tolower(readBuffer[i]);
			if (islower(readBuffer[i]))
				readBuffer[i] = 'z' - (readBuffer[i] - 'a');
		}
		//send the result to parent
		write(toparent[1], readBuffer, strlen(readBuffer)+1);
	}
}

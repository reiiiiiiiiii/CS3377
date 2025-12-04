#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000

void runCommand(char *cmd) {
	//"tool arg1 arg2 arg3 ..."
	char *args[MAXLEN];
	int argc=0;
	//use strtok() to setup args
	//get the first token  "ls -l fun.c" --> "ls"
	args[argc++] = strtok(cmd, " \n");
	//keep getting the tokens until we get NULL
	while (args[argc++] = strtok(NULL, " \n"))
		;

	execvp(args[0], args);
	fprintf(stderr, "%s cannot be run.\n", args[0]);
}

int main() {
	//get a command from the user
	char command[MAXLEN];
	printf("Enter command: ");
	fgets(command, MAXLEN, stdin);
	//create a pipe and rewire for looping
	int fds[2];
	pipe(fds);
	//fds[1] --> 1, fds[0] --> 0
	dup2(fds[1], 1);
	dup2(fds[0], 0);
	close(fds[0]); close(fds[1]);
	//execute the command
	runCommand(command);
}

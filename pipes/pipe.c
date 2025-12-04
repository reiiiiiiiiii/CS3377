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
//Goal: pipe "command1 ..."  "command2 ..."
//should achieve the result of
//command1 ... | command2 ...
int main(int argc, char *argv[]) {
	int fds[2];
	pipe(fds); //fds[0] is for reading, fds[1] is for writing
	           //    0 is for reading, 1 is for writing -
	if (fork()) {
		//parent runs command2, it has to read from pipe
		dup2(fds[0], 0);
		close(fds[0]); close(fds[1]);
		//parent: run command2?
		runCommand(argv[2]);
	} else {
		//child runs command1, it has to write to pipe
		dup2(fds[1], 1);
		close(fds[0]); close(fds[1]);
		//child: run command1?
		runCommand(argv[1]);
	}
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000
char *quotes[MAXQUOTES];
int numQuotes = 0;
int fds[201][2];

//runs a simple command
//cmdname arg1 arg2 arg3 ...
void runCommand(char *command) {
	//split and assemble the arguments and invoke execvp()
	//use strtok(..)
	char *args[MAXLEN];
	int i=0;
	args[i] = strtok(command, " \t\n");
	while (args[i]) {
		args[++i] = strtok(NULL, " \t\n");	
	}
	
	execvp(args[0], args);
	perror("Cmd failed to run");
	exit(1);
}

//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 ....
void child(int i, char *commands[], int numCommands) {
	//rewire pipes to 0 and 1 
	//do NOT rewire 0 for the first command - leave it as std input
	//do NOT rewrite 1 for the last command - leave it as std output
	//close unnecessary pipes - for loop?
	//run ith command
	//runCommand(commands[i]);
	
	if (i > 0) dup2(fds[i-1][0], STDIN_FILENO);
	if (i < numCommands - 1) dup2(fds[i][1], STDOUT_FILENO);

	for(int j=0; j < numCommands - 1; j++) {
		close(fds[j][0]);
		close(fds[j][1]);
	}

	commands[i][strcspn(commands[i], "\n")] = '\0';
	runCommand(commands[i]);
	exit(1);
}

void processLine(char *line) {
	char *pipePtr = strchr(line, '|'); //does this command have | chars?
	char *equalPtr = strchr(line, '='); //does this command have =?
	if (pipePtr) { //not NULL - cmd1 | cmd2 | cmd3 ....
		//command has several sub-commands connected with pipes
		//setup commands array
		//setup pipes array
		//fork & create children --> invoke child(i) in a loop
		//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
		// invoke child(i) for the last command directly?
		
		char *commands[100];
		int numCommands = 0;

		// init commands aray
		char *token = strtok(line, "|\n");
		while (token) {
			commands[numCommands++] = token;
			token = strtok(NULL, "|\n");
		}

		// setup pipes
		for(int i = 0; i < numCommands - 1; i++) {
			pipe(fds[i]);
		}

		// fork and create children
		for(int i = 0; i < numCommands; i++) {
			if(!fork()) {
				child(i, commands, numCommands);
				exit(1);
			}
		}

		for(int i = 0; i < numCommands -1; i++) {
			close(fds[i][0]);
			close(fds[i][1]);
		}

		for(int i = 0; i < numCommands; i++) {
			wait(NULL);
		}
	} else if (equalPtr) { 
		//command has = operator, so 2 commands --> 2 processes	
		
		char *left = strtok(line, "=\n");
		char *right = strtok(NULL, "=\n");
		int numCommands = 2;

		left[strcspn(left, "\n")] = '\0';
		right[strcspn(right, "\n")] = '\0';

		pipe(fds[0]); // left -> right
		pipe(fds[1]); // right -> left

		// first cmd (left)
		if (!fork()) {
			dup2(fds[0][1], STDOUT_FILENO);
			dup2(fds[1][0], STDIN_FILENO);
			for(int i=0; i < numCommands; i++) {
				close(fds[i][0]);
				close(fds[i][1]);
			}
			runCommand(left);
		}

		// second cmd (right)
		if (!fork()) {
			dup2(fds[0][0], STDIN_FILENO);
			dup2(fds[1][1], STDOUT_FILENO);
			for(int i=0; i < numCommands; i++) {
				close(fds[i][0]);
				close(fds[i][1]);
			}
			runCommand(right);
		}

		for(int i=0; i < numCommands; i++) {
			close(fds[i][0]);
			close(fds[i][1]);
		}
		for(int i=0; i < numCommands; i++) wait(NULL);
	} else 
		//it is a simple command, no pipe or = character
		runCommand(line);

	exit(0);
}

int main() {
	// load up all the quotes from quotes.txt - look at quoteserver.c for the code
	// infinite loop to serve the customer
	char line[1000];

	FILE *fp = fopen("quotes.txt", "r");
	if (!fp) {
		puts("quotes.txt failed to open");
		exit(1);
	}
	int i=0;

	while(fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d quotes\n", numQuotes);
	
	srand(time(NULL) + getpid() + getuid());
	while (1) {
		//output a random quote to stderr
		fputs(quotes[rand()%numQuotes], stderr);
		fprintf(stderr, "# "); //show prompt to the user
		//get the user input -- command line
		fgets(line, 1000, stdin);

		//spawn a child for taking care of it
		if (fork() == 0) 
			processLine(line);

		//wait the child to finish the job!
		wait(NULL);
	}
}

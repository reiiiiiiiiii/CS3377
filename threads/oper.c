#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 1000

struct StateInfo {
	int index; 
	char operators[10];
	int resultSoFar;
};

/* Here is the usage:
 *
struct StateInfo state;
state.index = 0;
state.resultSoFar = atoi(argv[1]);
pthread_create(...,..., compute_thread, (void *) &state);

void *compute(void *ptr) {
	struct StateInfo *statep = (struct StateInfo *) ptr;
	statep->index, statep->resultSoFar;

	struct StateInfo state1 = *statep; //start with a copy of incoming state 
	state1.index++;
}
*/

//Usage example: operators2 5 2 10 7 6 
//Output from one process should be 5 - 2 + 10 - 7 = 6

//Make parent process the manager - it should collect all output from children through a pipe
//This way, when there is no output, we can output "No solutions!"
//merge pipe functonality from pipe3.c

int main(int argc, char *argv[]) {
	int fds[2] = {}; //this pipe is used for all children --> top parent messages.
	pipe(fds);
	if (fork()) {
		close(fds[1]); //parent will NOT write to this pipe - so let us close
		//keep reading the pipe and output
		//if no output at all, output No solutions!
		char readBuffer[MAXLEN];
		int n = 0;
		bool output = false;
		//following read() will break once there are NO writers left!
		while ((n = read(fds[0], readBuffer, MAXLEN)) > 0) {
			write(1, readBuffer, n);	
			output = true;
		}
		if (!output)
			puts("No solutions!");
		exit(0);
	}

	close(fds[0]); //no child will read from this pipe! 

	int operatorCount = argc - 3; //tool, output, last operand
	char operators[operatorCount];
	int expectedResult = atoi(argv[argc-1]);
	int resultSoFar = atoi(argv[1]);
	
	for(int i=0; i<operatorCount; i++) {
		int operand = atoi(argv[i+2]);
		//consider +, -, *, / for current operator
		if (!myfork()) {
			operators[i] = '+';
			resultSoFar += operand;
			continue;
		} 
		if (!myfork()) {
			operators[i] = '-';
			resultSoFar -= operand;
			continue;
		}
		if (!myfork()) {
			operators[i] = '*';
			resultSoFar *= operand;
			continue;
		}

		//parent process continues with /
		operators[i] = '/';
		resultSoFar /= operand;
	}
	//we should have 4^operatorCount processes at this point.	
	if (resultSoFar == expectedResult) {
		//instead of printf(), do sprintf(buffer, ) then write(fds[1], ...) to write to pipe
		char buffer[MAXLEN] = {}, temp[MAXLEN] = {};
		for(int i=0; i<operatorCount; i++) {
			//write to a temp buffer, keep appending to buffer
			sprintf(temp, "%s %c ", argv[i+1], operators[i]);
			//write(fds[1], buffer, strlen(buffer));
			strcat(buffer, temp);
		}
		sprintf(temp, "%s = %d\n", argv[argc-2], expectedResult);
		strcat(buffer, temp);
		write(fds[1], buffer, strlen(buffer));
	}

	//original parent has the most # of children: 3 * operatorCount
	//for(int i=0; i<3*operatorCount; i++) 
		//wait(NULL);
}

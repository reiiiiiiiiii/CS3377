#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 1000

char operators[100];
int fds[201][2];
int operatorCount=0;
int numPipes=0;

void child(int index) { // operators[index] specifies the operator for this child
	// configure pipes
	dup2(fds[2*index][0], 0); // first arg
	dup2(fds[2*index+1][0], 3); // second arg
	dup2(fds[2*index+2][1], 1); // output to next
	
	// close pipes (no orphans)
	for(int i=0; i < numPipes; i++) {
		close(fds[i][0]);
		close(fds[i][1]);
	}

	char ops[] = "+-*/";
	char *tools[] = {"add", "subtract", "multiply", "divide"};

	char op = operators[index];
	for(int i = 0; i < strlen(ops); i++) {
		if(op == ops[i]) {
			execl(tools[i], tools[i], NULL);
			perror("Fail");
			exit(1);
		}
	}
	fprintf(stderr, "Bad Operator: %c\n", operators[index]);
	exit(1);
}

int main(int argc, char *argv[]) {
	char line[MAXLEN], *temp;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	FILE *dataFile = fopen(argv[1], "r");
	//read the first line - it contains the configuration
	fgets(line, MAXLEN, dataFile); 

	// sample content for line: a + b - c
	strtok(line, " \n"); //skip the symbol representing variable/parameter
	while (temp = strtok(NULL, " \n")) {
		operators[operatorCount] = temp[0];
		//printf("operator: %c\n", operators[operatorCount]);
		operatorCount++;
		strtok(NULL, " \n"); //skip the symbol representing variable/parameter
	}

	//create the necessary # of pipes
	numPipes = operatorCount * 2 + 1;

	//CODE HERE!
	//loop: create that many pipes (numPipes) -- all pipes are created!
	for(int i = 0; i < numPipes; i++) {
		pipe(fds[i]);
	}

	//loop: create that many children (operatorCount) - each one invokes child(i)
	for(int i = 0; i < operatorCount; i++) {
		if(!fork()) {
			// printf("Child process created\n");
			child(i);
		} else {
			// printf("Parent process...\n");
		}
	}

	//proceed to read data from the file and keep pumping them into pipes and read result 
	//while (fscanf(dataFile, "%d", &value) > 0)
	//  write it to first pipe
	//	use loop to read remaining data in that line & keep pumping to pipes: for i --> pipe 2*i+1 
	//	read the final result from the final pipe (numPipes-1) & print
	int value;
	while(fscanf(dataFile, "%d", &value) > 0) {
		write(fds[0][1], &value, sizeof(int));

		for(int i = 1; i < numPipes - 1; i += 2) {
			fscanf(dataFile, "%d", &value);
			write(fds[i][1], &value, sizeof(int));
		}

		int res;
		read(fds[numPipes-1][0], &res, sizeof(int));
		printf("%d\n", res);
	}
}


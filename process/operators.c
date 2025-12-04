#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

pid_t myfork() {
	pid_t pid = fork();
	if(pid == -1) {
		//output err message and bail
		perror("fork() failure");
		exit(1);
	}
	return pid;
}

//Usage example: operators 5 2 10 7 6 
//Output from one process should be 5 - 2 + 10 - 7 = 6
int main(int argc, char *argv[]) {
	int operatorCount = argc - 3; //tool, output, last operand
	char operators[operatorCount];
	int expectedResult = atoi(argv[argc-1]);
	int res = atoi(argv[1]);

	for(int i = 0; i < operatorCount; i++) {
		// +, -, *, /
		int operand = atoi(argv[i+2]);
		if(!myfork()) {
			operators[i] = '+';
			res += operand;
			continue;
		}
		if(!myfork()) {
			operators[i] = '-';
			res -= operand;
			continue;
		}
		if(!myfork()) {
			operators[i] = '*';
			res *= operand;
			continue;	
		}

		operators[i] = '/';
		res /= operand;	
	}
	if(res == expectedResult) {
		printf("%s ", argv[1]);
		for(int i = 0; i < operatorCount; i++) {
			printf("%c %s ", operators[i], argv[i+2]);
		}
		printf("= %d\n", res);
	}
	for(int i = 0; i < 3*operatorCount; i++) 
		wait(NULL);
}

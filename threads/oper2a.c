#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#define MAXLEN 1000

typedef struct {
	int index; 
	char operators[10];
	int resultSoFar;
} StateInfo;

char **gargv; //compute_thread() can now access argv!
int operatorCount = 0; 
int expectedResult = 0;
// int outputLines = 0; //not needed 

void *compute_thread(void *ptr);

void mynewpthread(pthread_t *pth, StateInfo *s) {
	if (!pthread_create(pth, NULL, compute_thread, (void *) s))
		return;
	puts("Thread creation failed. Quitting...");
	abort();
}

void *compute_thread(void *ptr) {
	StateInfo *statep = (StateInfo *) ptr;
	char *buffer = (char *) calloc (MAXLEN, sizeof(char));

	if (statep->index == operatorCount) {
		if (statep->resultSoFar == expectedResult) {
			char temp[MAXLEN] = {};
			for(int i=0; i<operatorCount; i++) {
				sprintf(temp, "%s %c ", gargv[i+1], statep->operators[i]);
				strcat(buffer, temp);
			}
			sprintf(temp, "%s = %d\n", gargv[operatorCount+1], expectedResult);
			strcat(buffer, temp);
			//puts(buffer); //do NOT output the equation to the screen!
			return (void *) buffer;
		}
		return NULL;
	}

	int operand = atoi(gargv[statep->index+2]);
	int index = statep->index;
	statep->index++;
    pthread_t threads[4];
	
	StateInfo state1 = *statep, state2 = *statep, state3 = *statep, state4 = *statep;
	state1.operators[index] = '+';
	state1.resultSoFar += operand;
	mynewpthread(&threads[0], &state1);

	state2.operators[index] = '-';
	state2.resultSoFar -= operand;
	mynewpthread(&threads[1], &state2);
	
	state3.operators[index] = '*';
	state3.resultSoFar *= operand;
	mynewpthread(&threads[2], &state3);
	
	state4.operators[index] = '/';
	state4.resultSoFar /= operand;
	mynewpthread(&threads[3], &state4);
	
	void *ptr2;
	for(int i=0; i<4; i++) {
		pthread_join(threads[i], &ptr2);
		if (ptr2)
			strcat(buffer, (char *) ptr2);
	}
	if (strlen(buffer))
		return (void *) buffer;
	else
		return NULL;
}

int main(int argc, char **argv) {
	gargv = argv;

	operatorCount = argc - 3; //tool, output, last operand
	expectedResult = atoi(argv[argc-1]);
	
	StateInfo state;
	state.index = 0;
	state.resultSoFar = atoi(argv[1]);

    pthread_t thread;
	pthread_create(&thread, NULL, compute_thread, (void *) &state);

	void *ptr;
	pthread_join(thread, &ptr);
	if (ptr)
		puts((char *) ptr);
	else
		puts("No solutions!");
}


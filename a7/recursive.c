#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VALUES 100

#define NUM_OPERATIONS 5
char operations[] = {'+', '-', '*', '/', '%'};

int compute(int value1, char oper, int value2) {
    switch (oper) {
        case '+': return value1 + value2;
        case '-': return value1 - value2;
        case '*': return value1 * value2;
        case '/': return value1 / value2; 
        case '%': return value1 % value2;  
    }
    return 0;
}

int numValues = 0;
int values[MAX_VALUES];
//CODE HERE!
//recursive function!

void findOperator(int res, int start, int target, char operators[], bool *found) {
	// printf("%d, %d\n", res, start);
	if(start == numValues) {
		if(res == target) {
			*found = true;
			printf("%d ", values[0]);
			for(int i=0; i < numValues-1; i++) {
				printf("%c %d ", operators[i], values[i+1]);
			}
			printf("= %d\n", target);
		}
		return;
	}

	for(int i=0; i < NUM_OPERATIONS; i++) {
		int newRes = compute(res, operations[i], values[start]);
		operators[start-1] = operations[i];
		findOperator(newRes, start + 1, target, operators, found); 	
	}
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <num1> <num2> ... <result>\n", argv[0]);
        return 1;
    }
    
    numValues = argc - 2; // not including target
    for (int i = 0; i < numValues; i++) {
        values[i] = atoi(argv[i + 1]);
    	//printf("%d ", values[i]);
    }
       
    //CODE HERE! 
 	//invoke recursive function!   
	// if no solutions are found,
	// puts("No solutions!"); 
	
	int target = atoi(argv[argc-1]);
	char operators[numValues-1];
	bool found = false;
	findOperator(values[0], 1, atoi(argv[argc-1]), operators, &found);
	if(!found) puts("No solutions!");
    return 0;
}

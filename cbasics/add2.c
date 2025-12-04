#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Usage: add1 <num1> <num2> [num3 ...]
int main() {
	while (true) {
		int total = 0;
		printf("Enter a line of ints: ");
		char buffer[1000];
		fgets(buffer, 1000, stdin); // read line from std input
		char *token = strtok(buffer, " "); // init tokenizer & get first token
		while (token) {
			total += atoi(token);
			token = strtok(NULL, " "); // get next token
		}

		printf("Total: %d\n", total);
	}
}

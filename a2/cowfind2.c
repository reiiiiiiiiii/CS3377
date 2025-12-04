#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

int main() {
	scanf("%s", input);

	//strlen(input) returns the length of the string
	//access individual char: input[i]
	//CODE HERE!
	int t = 0;
	int d = 0;
	for(int i = 0; i < strlen(input) - 1; i++) {
		if(input[i] == '(' && input[i+1] == '(') {
			d++;
		} else if(input[i] == ')' && input[i+1] == ')') {
			t += d;
		}
	}
	printf("%d", t);
	printf("\n");
}

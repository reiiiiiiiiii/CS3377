#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	//argv[1] has your name.. split and output 2 names!
	char *input = argv[1];
	int len = strlen(input);
	char *endp = input + len; //end pointer

	//output the name for clone #1	
	// argv[1][i] <- --> input[i]
	//for(int i=0; i<len; i+=2)
		//putchar(input[i]);
	for(char *cp = input; cp < endp; cp += 2)
		putchar(*cp);
	putchar('\n');

	//output the name for clone #2
	putchar(toupper(input[1])); //make first letter uppercase!
	//for(int i=3; i<len; i+=2)
		//putchar(input[i]);
	for(char *cp = input+3; cp < endp; cp += 2)
		putchar(*cp);
	putchar('\n');
}

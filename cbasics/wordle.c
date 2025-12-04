#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	for(int i = 1; i < argc; i++) {
		if(strlen(argv[i]) != 5) {
			puts("Bad!");
			exit(1);
		}
	}
	puts("Good!");
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	for(int i = argc-1; i > 0; i--) {
		int len = strlen(argv[i]);
		for(int j = len-1; j >= 0; j--) {
			putchar(argv[i][j]);
		}
		putchar(' ');
	}
	putchar('\n');
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 8 
int main() {

	int n;
	char buf[BUFFSIZE];

	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if(write(STDOUT_FILENO, buf, n) != n) {
			perror("write error");
			exit(1);
		}
	}
}

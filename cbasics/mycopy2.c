#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 512 
int main() {

	size_t n;
	char buf[BUFFSIZE];

	while((n = fread(buf, 1, BUFFSIZE, stdin)) > 0) {
		if(fwrite(buf, 1, n, stdout) != n) {
			perror("write error");
			exit(1);
		}
	}
}

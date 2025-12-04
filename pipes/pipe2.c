#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fds[100][2];

int main() {
	int fd = open("pipe2.c", O_RDONLY); //fd 3 is assigned here!	
	printf("File open fd: %d\n", fd);

	for(int i=0; i<100; i++) {
		pipe(fds[i]);
		printf("read: %d, write: %d\n", fds[i][0], fds[i][1]);
		//close(fds[i][0]);
	}
}

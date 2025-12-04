#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *names[] = { "Jack", "Jill", "Bill", "Alex", "Hiya", "Nila", "Babu", "Maxx", "Phil" };
char *message = "My name is ";
int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int fd = open("fork.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
	write(fd, message, strlen(message));
	//parent should create exactly n children
	int i;
	for(i=0; i<n; i++)
		if (!fork()) // (fork() == 0) is this child process?
			break;
	
	write(fd, names[i], strlen(names[i]));
	write(fd, "!\n", 2);
	close(fd);
}

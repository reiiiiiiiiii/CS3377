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
	FILE *fp = fopen("fork3.txt", "w");
	fputs(message,fp);
	fflush(fp);
	//parent should create exactly n children
	int i;
	for(i=0; i<n; i++)
		if (!fork()) // (fork() == 0) is this child process?
			break;
	
	fprintf(fp, "%s!\n", names[i]);
	fclose(fp);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

//any argument coming in - will be considered as enabling debug output
int main(int argc, char *argv[])
{
	bool debugOutput = false;
	//any parameter enables debug output
	if (argc > 1)
		debugOutput = true;

	double x, y, z;
	//read first input from fd 0
	while (read(0, &x, sizeof(double)) > 0) {
		if (debugOutput)
			fprintf(stderr, "%s: Read #1: %lf\n", argv[0], x);
		if (read(3, &y, sizeof(double)) > 0) {
			z = x + y;
			write(1, &z, sizeof(double));
			if (debugOutput) 
				fprintf(stderr, "%s: Read #2: %lf\nResult: %lf\n", argv[0], y, z);
	//replace standard output with pipe output
		} else
			exit(1);
	}
	exit(0);
}	

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	double x, y, z;
	while (read(0, &x, sizeof(double)) > 0) {
		if (argc > 1)
			fprintf(stderr, "%s: Read #1: %lf\n", argv[0], x);
		if (read(3, &y, sizeof(double)) > 0) {
			z = x / y;
			write(1, &z, sizeof(double));
			if (argc > 1)
				fprintf(stderr, "%s: Read #2: %lf\nResult: %lf\n", argv[0], y, z);
		} else
			exit(1);
	}
	exit(0);
}	

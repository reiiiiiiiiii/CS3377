#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	fprintf(stderr, "user: pid %d parent pid %d\n", getpid(), getppid());
	//use current time to come with a random seed
	srand(time(NULL));
	//get a random number 1 to 100
	int number = rand() % 100 + 1;
	fprintf(stderr, "Random number: %d\n", number);

	int received;
	//keep reading a number, respond with < or > or =
	while (read(0, &received, sizeof(int))> 0) {
		if (received < number)
			write(1, ">", 1); //tell parent to go higher!
		else if (received > number)
			write(1, "<", 1); //tell parent to go lower!
		else {
			write(1, "=", 1); //tell parent it is perfect!
			break;
		}
	}
	fputs("Child: done.\n",stderr);
}

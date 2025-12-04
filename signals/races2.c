#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int counter = 0;

int flag = 0;

void sig_start(int signo) {
	counter = 0;
	flag = 1;
	signal(SIGUSR1, sig_start);
}

int i;

void sig_stop(int signo) {
	signal(SIGUSR2, sig_stop);
	printf("%d: %d %d\n", i, counter, flag);
	flag = 0;
}

int main(int argc, char *argv[]) {
	//create specified # of tasks
	for(i=1; i<atoi(argv[1]); i++)
		if (fork() == 0)
			break;

	signal(SIGUSR1, sig_start);
	signal(SIGUSR2, sig_stop);

	while (1) {
		counter = 0;
		while (!flag)
			; // sleep(1);
		while (flag)
			counter++;
	}
}


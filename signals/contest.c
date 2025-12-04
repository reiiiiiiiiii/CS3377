#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define TIME_ROUND 20 //contest every round 20 seconds

int score = 0;

int counter=0;

void alarm_received(int signo) {
	counter++;
	printf("Alarm received. Round %d over. Current score: %d\n", counter, score);


	//re-register signal() 
	signal(SIGALRM, alarm_received);

	//run the contest 3 rounds
	if (counter < 3)  
		alarm(TIME_ROUND);
	else
		exit(0);
}

int main() {

	srand(time(NULL) + getpid() + getuid());

	//when SIGALRM is received, invoke alarm_received()
	signal(SIGALRM, alarm_received);
	alarm(TIME_ROUND);

	while (1) {
		//generate 2 3-digit numbers
		//ask the user for total
		int num1 = rand() % 100;
		int num2 = rand() % 100;
		printf("%d + %d = ? ", num1, num2);

		int input=0;
		scanf("%d", &input);

		if (num1 + num2 == input) {
			score++;
			puts("Great!");
		} else
			puts("Wrong.");

		printf("Score: %d\n", score);
	}
}

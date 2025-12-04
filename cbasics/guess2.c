#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
int main() {
	srand(time(NULL) + getpid() + getuid());
	int num = rand() % 100 + 1;
	int tries = 0;

	while(true) {
		int guess;
		printf("Enter your guess: ");
		scanf("%d", &guess);
		tries++;
		if(guess == num) {
			printf("You got it in %d tries!\n", tries);
			return 0;
		} else if(guess > num) {
			printf("Go lower\n");
		} else {
			printf("Go higher\n");
		}
	}
}

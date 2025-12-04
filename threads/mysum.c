#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int x=0, y=0, z=0;
int xyready=0, zready=0;
void *add(void *arg) {
	while (1) {
		//wait until x and y are ready
		while (!xyready)
			;
		z = x + y;
		xyready = 0;
		zready=1; //indicate output is ready
	}
}
int main() {
     pthread_t thread1;
     pthread_create(&thread1, NULL, add, NULL);

	//create new thread to start in add() - look into simple.c
	while (1) {
		printf("Enter 2 numbers: ");
		if (scanf("%d%d", &x, &y) != 2)
			exit(1);
		xyready=1; //indicate to other thread that data is ready!
		while (!zready)
			;
		printf("Sum: %d\n", z);
		zready=0;
	}
}

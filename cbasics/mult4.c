#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int num = getpid();

	for(int i = 1; i <= 10; i++) {
		printf("%4d * %2d = %7d\n", num, i, num*i);
		
	}
}

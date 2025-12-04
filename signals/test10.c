#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	/*
	if (fork()) {
		while (1) {
			int x;
			scanf("%d", &x);
			printf("parent: %d\n", x);
		}
	} else {
		while (1) {
			int x;
			scanf("%d", &x);
			printf("child: %d\n", x);
		}
	} */
	
	for(int child=0; child<10; child++) 
		if (!fork()) {
			while (1) {
				int x;
				scanf("%d", &x);
				printf("child %d: %d\n", child, x);
			}
		}

	while (1) {
		int x;
		scanf("%d", &x);
		printf("parent: %d\n", x);
	}
	
}

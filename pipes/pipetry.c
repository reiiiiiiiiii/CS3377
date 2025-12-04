#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fds[2];
	//FILE *fp = fopen("pipe1.c", "r");
	//for(int i=0; i<100; i++) {
		pipe(fds);
		printf("Pipe fds: %d %d\n", fds[0], fds[1]);
	//}
	char *message = "Hello! Do you hear me?";
	write(fds[1], message, strlen(message)+1);

	char buffer[1000] = {};
	int n = read(fds[0], buffer, 1000);
	printf("I read %s\n", buffer);
}

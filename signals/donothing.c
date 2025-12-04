#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
	puts("I am busy doing nothing. Don't disturb me!");
	signal(SIGINT, SIG_IGN); // when user ^C,ignore
	signal(SIGQUIT, SIG_IGN);
	while (1) 
		;
}

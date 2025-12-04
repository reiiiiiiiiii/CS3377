#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

//Usage:   bah [-s] [-n count] 
int main(char argc, char *argv[]) {
	char ch;
	int repeatCount=1000;
	bool startFlag = false;

	//arguments processing
	while ((ch = getopt(argc, argv, "sn:")) != -1) {
		//option character
		switch(ch) {
			case 's': startFlag = true;
						break;
			case 'n': repeatCount = atoi(optarg);
						break;
			case '?':
				fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				exit(1);

			default:
				fprintf(stderr, "bah [-s] [-n count]\n");
				exit(2);
		}
	}

//startFlag is true --> send out ba 
	if (startFlag) {
		printf("ba\n"); //to other program
		fprintf(stderr, "bah!\n"); //to screen
		fflush(stdout); //ensures that other program got it!
	}

//for loop: get string, add b in front, a at the end, send it out and also display!
	char buffer[10000];
	for(int i=0; i<repeatCount; i++) 
		if (scanf("%s", buffer) == 1) {
			printf("b%sa\n", buffer);
			fprintf(stderr, "b%sah!\n", buffer);
			fflush(stdout);
		}
}

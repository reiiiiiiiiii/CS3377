#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

//Example: mecho -s 10 -n 10 17
//Usage:   mecho [-s startValue] [-n count] multiplier
int main(char argc, char *argv[]) {
	char ch;
	long startingValue=0, repeatCount=1000, multiplier=1, inputValue=0;

	//arguments processing
	while ((ch = getopt(argc, argv, "s:n:")) != -1) {
		//option character
		switch(ch) {
			case 's': startingValue = atoi(optarg);
						break;
			case 'n': repeatCount = atoi(optarg);
						break;
			case '?':
				fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				exit(1);

			default:
				fprintf(stderr, "mecho [-s startValue] [-n count] multiplier\n");
				exit(2);
		}
	}
	if (optind < argc) 
		multiplier = atol(argv[optind]);
	else {
		fprintf(stderr, "mecho [-s startValue] [-n count] multiplier\n");
		exit(3);
	}

	//if command specified starting value, go ahead and send it out!
	if (startingValue) {
		printf("%ld\n", startingValue); //to other program
		fprintf(stderr, "%ld\n", startingValue); //to screen
		fflush(stdout); //ensures that other program got it!
	}

	for(int i=0; i<repeatCount; i++) 
		if (scanf("%ld", &inputValue) == 1) {
			printf("%ld\n", inputValue * multiplier);
			fprintf(stderr, "%ld\n", inputValue * multiplier);
			fflush(stdout);
		}
}

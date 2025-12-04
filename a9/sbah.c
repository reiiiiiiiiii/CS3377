#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

//Usage:   bah [-s startString] [-n repeatCount] prefixString [suffixString]
int main(char argc, char *argv[]) {
	char ch;
	int repeatCount=1000;
	char *startString=NULL, *prefixString=NULL, *suffixString=NULL;
	//arguments processing
	while ((ch = getopt(argc, argv, "s:n:")) != -1) {
		//option character
		switch(ch) {
			case 's': startString = optarg; //points to argv[i]
						break;
			case 'n': repeatCount = atoi(optarg);
						break;
			case '?':
				fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				exit(1);

			default:
				fprintf(stderr, "bah [-s startString] [-n repeatCount] prefixString [suffixString]\n");
				exit(2);
		}
	}

	if (optind < argc) {
		//set prefixString, suffixString
		suffixString = prefixString = argv[optind]; //set both strings to same arg for now!
		if (optind+1 < argc) //is there 2nd argument?
			suffixString = argv[optind+1];
	} else {
		fprintf(stderr, "bah [-s startString] [-n repeatCount] prefixString [suffixString]\n");
		exit(3);
	}

//startFlag is true --> send out ba 
	if (startString) {
		printf("%s\n", startString); //to other program
		fprintf(stderr, "%s\n", startString); //to screen
		fflush(stdout); //ensures that other program got it!
	}

//for loop: get string, add b in front, a at the end, send it out and also display!
	char buffer[10000];
	for(int i=0; i<repeatCount; i++) 
		if (scanf("%s", buffer) == 1) {
			printf("%s%s%s\n", prefixString, buffer, suffixString);
			fprintf(stderr, "%s%s%s\n", prefixString, buffer, suffixString);
			fflush(stdout);
		}
}

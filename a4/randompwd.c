#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if(argc != 7) {
		printf("Usage: randompwd <minlen> <maxlen> <minLower> <minUpper> <minDigits> <minSpecial>");
		return -1;
	}
	
	int minlen = atoi(argv[1]);
	int maxlen = atoi(argv[2]);
	int minLower = atoi(argv[3]);
	int minUpper = atoi(argv[4]);
	int minDigits = atoi(argv[5]);
	int minSpecial = atoi(argv[6]);

	if(minLower + minUpper + minDigits + minSpecial > maxlen) {
		printf("Too many mins");
		return -1;
	}

	srand(time(NULL) + getpid() + getuid());
	char passwrd[maxlen];
	int randlen = minlen + rand() % (maxlen - minlen + 1);

	int i = 0;
	for(int j = 0; j < minLower; j++) {
		passwrd[i++] = 'a' + rand() % 26;
	}
	for(int j = 0; j < minUpper; j++) {
		passwrd[i++] = 'A' + rand() % 26;
	}
	for(int j = 0; j < minDigits; j++) {
		passwrd[i++] = '0' + rand() % 10;
	}

	const char special[] = "!@#$%^&*+:;";
	int specialLen = strlen(special);
	for(int j = 0; j < minSpecial; j++) {
		passwrd[i++] = special[rand() % specialLen];
	}
	
	while(i < randlen) {
		int randChar = rand() % 4;
		if(randChar == 0) passwrd[i++] = 'a' + rand() % 26;
		else if(randChar == 1) passwrd[i++] = 'A' + rand() % 26;
		else if(randChar == 2) passwrd[i++] = '0' + rand() % 10;
		else passwrd[i++] = special[rand() % specialLen];
	}
	
	passwrd[i] = '\0';
	printf("%s\n", passwrd);	
}


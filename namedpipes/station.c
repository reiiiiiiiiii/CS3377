#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000
/*
//pointers to store the quotes
char *quotes[MAXQUOTES];
int numQuotes=0;
*/
int main() {
	char line[MAXLEN];

	/*
	FILE *fp = fopen("quotes.txt", "r");
	if (!fp) {
		puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while (fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d quotes were read.\n", numQuotes);

	srand(getpid() + time(NULL) + getuid());
	// puts(quotes[rand() % numQuotes]);
	*/

	//create a named pipes to read client's requests
	char filename[MAXLEN];
	//sprintf - string printf
	sprintf(filename, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(filename, 0600);
	chmod(filename, 0622); //enable other users to write to this pipe
	printf("Send your requests to %s\n", filename);

	int callerNumber = 1;
	while (1) {
		FILE *fp = fopen(filename, "r");
		if (!fp) {
			printf("FIFO %s cannot be opened for reading.\n", filename);
			exit(2);
		}
		printf("Opened %s to read...\n", filename);
		while (fgets(line, MAXLEN, fp)) {
			//fgets reads and puts \n at the end of buffer
			//get rid of it, before using the line like filename
			char *cptr = strchr(line, '\n');
			if (cptr) 
				*cptr = '\0';

			FILE *clientfp = fopen(line, "w");
			printf("%s:\n", line);
			if (clientfp) {
				//caller number 5 or 10 --> Congrats! You got free tickets!!
				//else: Sorry, you are caller # ...
				/*
				int quoteNumber = rand() % numQuotes;
				printf("%s\n", quotes[quoteNumber]);
				fputs(quotes[quoteNumber], clientfp);
				*/
				if (callerNumber % 5 == 0)
					fprintf(clientfp, "Congrats! You got FREE tickets.\n");
				else
					fprintf(clientfp, "Sorry, you are caller # %d\n", callerNumber);
				printf("Caller # %d\n", callerNumber); //to display
				fclose(clientfp);
				callerNumber++;
				if (callerNumber > 10)
					exit(0);
			}
			putchar('\n');
		}
		fclose(fp);
	}
}

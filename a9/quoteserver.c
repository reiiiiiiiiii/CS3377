#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

//read all the quotes from quotes.txt

#define MAXQUOTES 10000
#define MAXLEN 1000

//char quotes[MAXQUOTES][MAXLEN]; -- no need for further memory allocation, we can read quotes directly!
char *quotes[MAXQUOTES]; //a bunch of pointers!
//char **quotes; //count the # of quotes first.
//quotes = (char **) malloc (sizeof(char *) * numQuotes);
int numQuotes=0;

int main() {
	char line[MAXLEN];

	FILE *fp = fopen("quotes.txt", "r");
	if (!fp) {
		puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while ((i < MAXQUOTES) && fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d quotes were read.\n", numQuotes);

	srand(getpid() + time(NULL) + getuid());
	puts(quotes[rand()%numQuotes]); //output a random quote!

}

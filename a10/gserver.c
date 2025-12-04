/*
 * read dictionary file to array of words & get ready to play the hangman!
if you are using fgets() to read the word
	  cptr = strchr(line, '\n');
	  if (cptr)
	  	*cptr = '\0';
 However, since we are dealing with words, you can use fscanf(...,"%s", ...) instead!

 * wait for a request to come in (client specifies unique pipename)
 * select a random word using rand()
 * fork() to create a child to handle this client! (dedicated server process for that client)
 * fork() enables games to proceed in parallel. Parent returns to wait for new client requests
 * respond with another unique server-side pipename 
 

 * send a bunch of stars (indicating the word length)
 * for each guess the client sends in, respond with a message 
 * and send updated display word.
 *
 * Whenever you send strings through named pipes, 
 * terminate with '\n' and also do fflush() for that data to make it to other side without getting stuck
 * in buffers.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <signal.h>

#define MAXWORDS 100000
#define MAXLEN 1000

char *words[MAXWORDS];
int numWords = 0;

int main() {
	char line[MAXLEN];

	FILE *fp = fopen("dictionary.txt", "r");
	if (!fp) {
		puts("dictionary.txt cannot be opened for reading\n");
		exit(1);
	}
	int i=0;

	char buffer[MAXLEN];
	while(fscanf(fp, "%s", buffer) == 1) {
		words[i] = (char *) malloc (strlen(buffer)+1);
		strcpy(words[i], buffer);
		i++;
	}
	
	numWords = i;
	
	// create named pipes for client
	char filename[MAXLEN];
	sprintf(filename, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(filename, 0600);
	chmod(filename, 0622);
	printf("Send your requests to %s\n", filename);

	while (1) {
		FILE *fp = fopen(filename, "r");
		if (!fp) {
			printf("FIFO %s could not be opened.\n", filename);
			exit(2);
		}
		printf("Opened %s to read...\n", filename);

		while (fgets(line, MAXLEN, fp)) {

			char *cptr = strchr(line, '\n');
			if (cptr) *cptr = '\0';
			
			// create child for client
			if (!fork()) {
				FILE *clientfp = fopen(line, "w");
				

				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), getpid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);

				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);

				FILE *serverfp = fopen(serverfifo, "r");

				// select random word
				// send to client
				// check off correct guesses and incorrect guesses
				
				srand(getpid() + time(NULL) + getuid());
				char *selectedWord = words[rand() % numWords];
				int wordlen = strlen(selectedWord);
				char starredWord[wordlen+1];
				for(int j=0; j<wordlen; j++) {
					starredWord[j] = '*';
				}
				starredWord[wordlen] = '\0';

				int incorrect = 0;
				int correct = 0;
				
				// printf("Word: %s\t Length: %d\n", selectedWord, wordlen);
				
				while(1) {
					fprintf(clientfp, "Enter a letter in word %s > \n", starredWord);
					fflush(clientfp);
					
					
					do {
						if(!fgets(line, MAXLEN, serverfp)) break;
					} while (line[0] == '\n' || line[0] == '\0');
					
					// printf("|%s|\n", line);
					char guess = line[0];
					
					bool found = false;
					bool alreadyFound = false;
					
					for(int i=0; i<wordlen; i++) {
						if(selectedWord[i] == guess) {
							if(starredWord[i] == '*') {
								found = true;
								correct++;
								starredWord[i] = selectedWord[i];
							} else {
								alreadyFound = true;
							}
						}
					}
					
					if (alreadyFound) {
						fprintf(clientfp, "%c is already in the word\n", guess);
					} else if (!found) {
						fprintf(clientfp, "%c is not in the word\n", guess);
						incorrect++;
					} else {
						// fprintf(clientfp, "correct guess\n");
					}
					fflush(clientfp);
					if (correct == wordlen) {
						fprintf(clientfp, "The word is %s. You missed %d times.\n", selectedWord, incorrect);
						fflush(clientfp);
						break;
					}
		
					// puts(starredWord);
					// printf("%d\n", correct);	
				}
				

				fclose(clientfp);
				fclose(serverfp);

				unlink(serverfifo);
				exit(0);
			}
		}
	}
}

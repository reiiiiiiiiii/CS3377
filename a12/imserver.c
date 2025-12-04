#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>

#define MAXWORDS 10000
#define MAXLEN 1000
#define MAXCLIENTS 100

char usernames[MAXCLIENTS][MAXLEN];
FILE *clientfps[MAXCLIENTS]; //to write to each client
int numClients = 0;

void *server_child(void *ptr) {
	int clientIndex = *((int *) ptr);
	free(ptr);
	//create dedicated server fifo - use pthread_self() instead of getpid() to create unique server fifo
	//send it to the client - clientfps[clientIndex]
	//wait to read from client in a loop
	//process the command
	FILE *clientfp = clientfps[clientIndex];
	//create and send new server fifo to the client
	//for private one-on-one communcations
	char serverfifo[MAXLEN];
	sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), pthread_self());
	mkfifo(serverfifo, 0600);
	chmod(serverfifo, 0622);
	fprintf(clientfp, "%s\n", serverfifo);
	fflush(clientfp);

	FILE *serverfp = fopen(serverfifo, "r");

	//actual server logic!
	char line[MAXLEN];
	char *username = usernames[clientIndex];
	fprintf(clientfp, "Welcome!\n");
	printf("%s has joined!\n", username);
	fflush(clientfp);

	while(fgets(line, MAXLEN, serverfp)) {
		char *cmd = strtok(line, " \n");
		if(cmd == NULL) continue;

		if(strcmp(cmd, "list") == 0) {
			for(int i=0; i<numClients; i++) {
				fprintf(clientfp, "%s ", usernames[i]);
			}
			fprintf(clientfp, "\n");
			fflush(clientfp);
		} else if(strcmp(cmd, "send") == 0) {
			char *user = strtok(NULL, " \n");
			char *message = strtok(NULL, "\n");
			
			if (!user || !message) {
				fprintf(clientfp, "Usage: send <user> <message>\n");
				fflush(clientfp);
				continue;
			}


			puts(user);
			puts(message);
			bool found = false;
			for(int i=0; i<numClients; i++) {
				if(strcmp(user, usernames[i]) == 0) {
					FILE *userfp = clientfps[i];
					fprintf(userfp, "%s: %s\n", username, message);
					fflush(userfp);
					fprintf(clientfp, "Message Sent\n");
					fflush(clientfp);
					found = true;
				}
			}
			if(!found) {
				fprintf(clientfp, "User not found\n");
				fflush(clientfp);
			}

		}
	}
	
	fclose(clientfp);
	fclose(serverfp);
		
	unlink(serverfifo);

	return (void *) clientIndex;
}

int main() {
	char line[MAXLEN];

	srand(getpid() + time(NULL) + getuid());
	// puts(words[rand() % numWords]);
	
	//create a named pipes to read client's requests
	char filename[MAXLEN];
	sprintf(filename, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(filename, 0600);
	chmod(filename, 0622);
	printf("Send your requests to %s\n", filename);

	while (1) {
		FILE *fp = fopen(filename, "r");
		if (!fp) {
			printf("FIFO %s cannot be opened for reading.\n", filename);
			exit(2);
		}
		printf("Opened %s to read...\n", filename);

		//wait for clients' requests
		while (fgets(line, MAXLEN, fp)) {

			//use strtok() to get clientfifo and username
			char *clientfifo = strtok(line, " \n");
			char *userName = strtok(NULL, " \n");
			//create a server_child thread instead of fork(), move the following code there and continue...
			//use pthread_self() instead of getpid()
			clientfps[numClients] = fopen(clientfifo, "w");
			userName[strcspn(userName, "\n")] = '\0';
			strcpy(usernames[numClients], userName);
			
			pthread_t thread;
			
			int *clientIndex = malloc(sizeof(int));
			*clientIndex = numClients;
			pthread_create(&thread, NULL, server_child, (void *) clientIndex);
			
			pthread_detach(thread);
			
			numClients++;
		}
		fclose(fp);
	}
}


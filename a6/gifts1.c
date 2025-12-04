#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//let us assume that there will not be more than 100 players
#define MAXPLAYERS 100
//let us assume that max length for any name is 100 characters
#define MAXLEN 100


//arrays to store the player names and balances
char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, names[i]) == 0)
               return i;

        return -1;
}

int main(int argc, char *argv[]) {
	//code here! use the following code just as reference 

	if(strcmp(argv[1], "new") == 0) { // initialize new players
		FILE *fp = fopen("gifts1.txt", "w");
		int idx = 0;
		// print and write players to file
		for(int i = 2; i < argc; i = i+2) {
			strcpy(names[idx], argv[i]);
			balances[idx] = atof(argv[i+1]);
			printf("%10s: %6.2lf\n", names[idx], balances[idx]);
			fprintf(fp, "%s %.2lf\n", names[idx], balances[idx]);
		}
		numPlayers = idx;

		fclose(fp);
	} else { // perform transacction
		int idx = 0;
		FILE *fp = fopen("gifts1.txt", "r");
		// init players
		while(fscanf(fp, "%s %lf", names[idx], &balances[idx]) == 2) {
			idx++;
		}
		numPlayers = idx;
		
		fclose(fp);
		int p1 = findIndex(argv[1]);
		if(p1 == -1) {
			printf("Player not found");
			return 1;
		}
		double amt = atof(argv[2]);
		int split = argc-3;
		balances[p1] -= amt;
		// give each player points
		for(int i=0; i < split; i++) {
			int pIndex = findIndex(argv[i+3]);
			balances[pIndex] += amt/split;
		}
		
		// print and write players to file
		fp = fopen("gifts1.txt", "w");
		for(int i=0; i < numPlayers; i++) {
			printf("%10s: %6.2lf\n", names[i], balances[i]);
			fprintf(fp, "%s %.2lf\n", names[i], balances[i]);
		}
		fclose(fp);
	}
}

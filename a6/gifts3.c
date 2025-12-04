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

struct Player {
	char name[MAXLEN];
	double balance;
} ;

//struct is like class - we can use an array of struct (we can use like an array of objects).
struct Player players[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, players[i].name) == 0)
               return i;

        return -1;
}

// use binary data file gifts3.dat to read and store the results.

int main(int argc, char *argv[]) {
	if(strcmp(argv[1], "new") == 0) { // init new players
		FILE *fp = fopen("gifts3.dat", "wb");
		int idx = 0;
		// read player data and put in array
		for(int i = 2; i < argc; i += 2) {
			strcpy(players[idx].name, argv[i]);
			players[idx].balance = atof(argv[i+1]);
			printf("%10s: %6.2lf\n", players[idx].name, players[idx].balance);
			idx++;
		}
		numPlayers = idx;
		fwrite(players, sizeof(struct Player), numPlayers, fp); // write to file
		fclose(fp);
	} else { // perform transaction
		FILE *fp = fopen("gifts3.dat", "rb");
		numPlayers = fread(players, sizeof(struct Player), MAXPLAYERS, fp); // init players
		fclose(fp);
		fp = fopen("gifts3.dat", "wb");

		// split and give points to each player
		int p1 = findIndex(argv[1]);
		double amt = atof(argv[2]);
		int split = argc-3;
		players[p1].balance -= amt;
		for(int i=0; i < split; i++) {
			int pIndex = findIndex(argv[i+3]);
			players[pIndex].balance += amt/split;
		}
		
		// print all players
		for(int i=0; i < numPlayers; i++) {
			printf("%10s: %6.2lf\n", players[i].name, players[i].balance);
		}

		fwrite(players, sizeof(struct Player), numPlayers, fp); // write to file
		fclose(fp);
	}
}

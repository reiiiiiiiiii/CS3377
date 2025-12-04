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

// write player data to .dat
void writeToFile() {
	int fd = open("gifts2.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	for(int i=0; i < numPlayers; i++) {
		int namelen = strlen(names[i]);
		write(fd, &namelen, sizeof(int));
		write(fd, names[i], namelen);
		write(fd, &balances[i], sizeof(double));
		printf("%10s: %6.2lf\n", names[i], balances[i]);
	}
	close(fd);
}

// use binary data file gifts2.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	//following line makes sense only for writing to file
	//int fd = open("gifts2.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	//if the command is not "new",
	//int fd = open("gifts2.dat", O_RDONLY);

	//how to write and read individual name?
	//simplest approach is to write the name length first, then the actual content
	//to make reading the name from file easier.
	//write(fd, balances, sizeof(double));
	//close(fd);
	//
	
	if(strcmp(argv[1], "new") == 0) { // init new players
		int idx = 0;
		for(int i = 2; i < argc; i += 2) {
			strcpy(names[idx], argv[i]);
			balances[idx] = atof(argv[i+1]);
			idx++;
		}
		numPlayers = idx;
		writeToFile(); // write players to file
	} else { // perform transaction
		int fd = open("gifts2.dat", O_RDONLY);
		int namelen = 0;
		int idx = 0;
		// read each player in dat and store in arrays
		while(read(fd, &namelen, sizeof(int)) > 0) {
			read(fd, names[idx], namelen);
			read(fd, &balances[idx], sizeof(double));
			idx++;
		}
		numPlayers = idx;
		close(fd);
		fd = open("gifts2.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		int p1 = findIndex(argv[1]);
		if(p1 == -1) {
			printf("Player doesn't exist");
			return 1;
		}
		
		// split and give points to players
		double amt = atof(argv[2]);
		int split = argc-3;
		balances[p1] -= amt;
		for(int i=0; i < split; i++) {
			int pIndex = findIndex(argv[i+3]);
			balances[pIndex] += amt/split;
		}
		close(fd);
		writeToFile(); // write players to file
	}
}

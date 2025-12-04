#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

long computeOverheadBlocks(long diskblocks) {
	//CODE HERE!
	if(diskblocks <= 12) return 0;
	if(diskblocks <= 2060) return 1;
	long ohBlocks =2;
	diskblocks -= 2060;

	int i;
	int j;
	for(i = 0; i < 2048; i++) {
		diskblocks -= 2048;
		ohBlocks++;
		if(diskblocks <= 0) return ohBlocks;
	}
	
	ohBlocks++;
	for(i = 0; i < 2048; i++) {
		ohBlocks++;
		for(j = 0; j < 2048; j++) {
			diskblocks -= 2048;
			ohBlocks++;
			if(diskblocks <= 0) return ohBlocks;
		}
	}	
	
	return -1;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: diskblocks <file size in KBs>\n");
		return -1;
	}

	//input file size is in KB.. 
	long filesize = atol(argv[1]);
	long diskblocks = filesize / 8;
	if (filesize % 8) 
		diskblocks++;
	//Alternate approach is to use ceil(). diskblocks = ceil(filesize / 8.0);

	printf("%ld %ld\n", diskblocks, computeOverheadBlocks(diskblocks));
}

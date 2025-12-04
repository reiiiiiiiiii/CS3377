#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16

//use one command line argument
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: diagonal <textstring>\n");
		return -1;
	}
	
	//create a file so that 16 rows of empty will appear with od -c command
	int fd = open("diagonal2.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	char space = ' ';
	for(int i = 1; i < argc; i++) {		
		for(int line=0; line<LINESIZE; line++)
			for(int column=0; column<LINESIZE; column++)
				write(fd, &space, 1);
	}
	
	//Each line of od outputs 16 characters 
	//So, to make the output diagonal, we will use 0, 17, 34, ....
	int chng = 1;
	int spot = 0;
	for(int i = 1; i < argc; i++) {
		int n = strlen(argv[i]);
		int idx = 0;
		int start = (i-1) * LINESIZE * LINESIZE;
		while(idx < n) {
			lseek(fd, (LINESIZE) * idx + spot + start, SEEK_SET);
			write(fd, &argv[i][idx++], 1);
			spot += chng;			
		}
		spot = chng > 0 ? 15 : 0;
		chng *= -1;	
	}
	close(fd);
	puts("diagonal2.out has been created. Use od -c diagonal2.out to see the contents.");
}

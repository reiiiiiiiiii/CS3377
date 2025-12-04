#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//get the command from the user
//split them into words: strtok()
//then invoke the program with those argument list
int main()
{
	char command[1000] = {};
	printf("Enter command: ");
	fgets(command, 1000, stdin);
	
	char *args[100] = {};
	args[0] = strtok(command, " \n");
	int i=1;
	while (args[i] = strtok(NULL, " \n"))
		i++;

	execvp(args[0],args);
      
    //All statements are ignored after execvp() 
    printf("I hope you won't see me!");
      
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	//ask the user for a program name
	char programName[100];
	printf("Enter program name: ");
	scanf("%s", programName);

	//invoke it instead of "child"
	
	//A null terminated array of character pointers 
	char *args[]={programName, NULL}; 
	execvp(args[0],args);
      
    //All statements are ignored after execvp() 
    puts("Invalid command!");
      
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	//A null terminated array of character pointers 
	char *args[]={"childd",NULL}; 
	execvp(args[0],args);
      
    //All statements are ignored after execvp() 
    printf("I hope you won't see me!\n");
    printf("errno %d\n", errno);
    perror("");
    return 0;
}

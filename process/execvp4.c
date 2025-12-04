#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	execvp(argv[1], argv+1);
      
    //All statements are ignored after execvp() 
    puts("I hope you won't see me!");
      
    return 0;
}

//Source: https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int limit=0;

//return type and parameter type dictated by thread creation mechanism
//void * means pointer to memory, but we have no idea what data type it is pointing to.
void *go_sleep( void *ptr )
{
	puts("Going to sleep...");
	sleep(100);
}

int main(int argc, char *argv[])
{
    /* Create independent threads each of which will execute function */
	int n = atoi(argv[1]);
     pthread_t threads[n];

	for(int i=0; i<n; i++)
     if (pthread_create(&threads[i], NULL, go_sleep, NULL)) {
	 	fprintf(stderr, "Thread creation failed for %d\n", i);
     	exit(1);
	 }

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

	for(int i=0; i<n; i++)
     	pthread_join(threads[i], NULL);

     exit(0);
}


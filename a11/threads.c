#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numThreads; //we should use threads 0, 1, 2, 3....(numThreads-1)

void *work( void *ptr )
{
	int n = (int) ptr;
	printf("I am thread %d\n", n);
	//parent n --> children 2n+1 and 2n+2
	
     pthread_t thread1, thread2;
	
     if (2*n+1 < numThreads) { //ok to create 1st child?
     	pthread_create(&thread1, NULL, work, (void *) (2*n+1));
		if (2*n+2 < numThreads) { //ok to create 2nd child?
     		pthread_create(&thread2, NULL, work, (void *) (2*n+2));
     		pthread_join(thread2, NULL);
		}
     	pthread_join(thread1, NULL);
	}
}

int main(int argc, char *argv[])
{
     pthread_t thread1;
	 numThreads = atoi(argv[1]);  //# of threads
     pthread_create(&thread1, NULL, work, (void *) 0);
     pthread_join(thread1, NULL);
}



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *function_for_thread(void *ptr) {
	int n = *(int *) ptr;
	int *sump = (int *) malloc( sizeof(int));
	*sump = 1;
	if (n < 2)
		return (void *) sump;
	//create 2 threads, add results, return total
	int n1 = n-1, n2 = n-2;
	pthread_t thread1, thread2;
	if (pthread_create(&thread1, NULL, function_for_thread, (void *) &n1))
    		exit(1);
	if (pthread_create(&thread2, NULL, function_for_thread, (void *) &n2))
    		exit(1);
	void *ptr1, *ptr2;
	pthread_join(thread1, &ptr1);
	pthread_join(thread2, &ptr2);
	
	*sump = *(int *) ptr1 + *(int *) ptr2;
	
	free(ptr1); free(ptr2);

	printf("fib(%d) = %d\n", n, *sump);
	return (void *) sump;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
    pthread_t thread1;
    if (pthread_create(&thread1, NULL, function_for_thread, (void *) &n))
    	exit(1);

	void *ptr;
    pthread_join(thread1, &ptr);
    free(ptr);
	printf("fib(%d) = %d\n", n, *(int *) ptr);
    exit(0);
}


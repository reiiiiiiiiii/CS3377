#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#define MAXLEN 1000

typedef struct {
	int *values;
	int n;
} MergeData;

char **gargv; //compute_thread() can now access argv!
int operatorCount = 0; 
int expectedResult = 0;
// int outputLines = 0; //not needed 

void *merge(void *ptr);

void *mergeSort(void *ptr) {
	MergeData *start = (MergeData *) ptr;
	int n = start->n;
	int *values = start->values;

	if (n <= 1) return NULL;

	int half = n/2;
	MergeData left = { values, half};
	MergeData right = { values + half, n - half };

	pthread_t t1, t2;

	pthread_create(&t1, NULL, mergeSort, &left);
	pthread_create(&t2, NULL, mergeSort, &right);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	merge(ptr);
}

void *merge(void *ptr) {
	MergeData *start = (MergeData *) ptr;
	int n = start->n;
	int *values = start->values;
	
	int *temp = malloc (n * sizeof(int));	
	memcpy(temp, values, n * sizeof(int));

	int len1 = n/2;
	int len2 = n - n/2;
	int i=0, j=0, k=0;
	int *first = temp, *second = &temp[len1];

	while (i < len1 && j < len2)
		values[k++] = (first[i] < second[j] ? first[i++] : second[j++]);
	while (i < len1)
		values[k++] = first[i++];
	while (j < len2)
		values[k++] = second[j++];
	
	free(temp);
}


int main(int argc, char **argv) {
	int n = 0;
	int array[100];
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &array[i]);
	MergeData start = { array, n };
	
	pthread_t thread;
	pthread_create(&thread, NULL, mergeSort, (void *) &start);

	void *ptr;
	pthread_join(thread, &ptr);

	for (int i=0; i<n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

#include <stdio.h>     
#include <stdlib.h>   
#include <stdint.h>  
#include <inttypes.h>  
#include <errno.h>     // for EINTR
#include <fcntl.h>     
#include <unistd.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdbool.h>

// Print out the usage of the program and exit.
void usage(char*);
uint32_t jenkins_one_at_a_time_hash(const uint8_t* , uint64_t );
int num_threads;
int chunk_size;
int32_t fd;


void *child(void* ptr) {
	uint32_t n = (uint32_t) ptr;
	
	pthread_t thread1, thread2;
	bool leftChild = false, rightChild = false;
	// Perfect binary tree structure:
	// LeftChild: 2*n+1 | RightChild: 2*n+2
	if (2*n+1 < num_threads) {
		pthread_create(&thread1, NULL, child, (void *) (2*n+1));
		leftChild = true;
		if (2*n+2 < num_threads) {
			pthread_create(&thread2, NULL, child, (void *) (2*n+2));
			rightChild = true;
		}
	}

	char *buffer = (char *) malloc (chunk_size);
	if (!buffer) {
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}

	off_t offset = n * chunk_size;
	ssize_t bytes = pread(fd, buffer, chunk_size, offset);

	uint32_t hash = jenkins_one_at_a_time_hash(buffer, chunk_size);

	void *ptr1 = NULL, *ptr2 = NULL;
	if (leftChild) pthread_join(thread1, &ptr1);
	if (rightChild) pthread_join(thread2, &ptr2);

	char temp[1000];
	uint32_t final_hash = hash;

	if(ptr1 && ptr2) {
		snprintf(temp, sizeof(temp), "%u%u%u", hash, ptr1, ptr2);
		final_hash = jenkins_one_at_a_time_hash(temp, (uint32_t) strlen(temp));
	} else if(ptr1) {
		snprintf(temp, sizeof(temp), "%u%u", hash, ptr1);
		final_hash = jenkins_one_at_a_time_hash(temp, (uint32_t) strlen(temp));
	}

	return (void *) final_hash;
	
}

int main(int argc, char *argv[]) 
{
  // input checking 
  if (argc != 3)
    usage(argv[0]);


  // open input file
  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }

  // use fstat to get file size
  struct stat fileInfo;
  if (fstat(fd, &fileInfo)) {
		perror("file not found.");
		exit(EXIT_FAILURE);
	}
  uint64_t fileSize = fileInfo.st_size;

  num_threads = atoi(argv[2]);
  chunk_size = fileSize / num_threads;

  /*
  char *buffer = (char *) malloc (fileSize);
  if (buffer == NULL) {
		perror("Memory allocation failure.");
		exit(EXIT_FAILURE);
  }
  uint64_t nread = 0;
  ssize_t n = 0;
  //as long as there is more data to read, keep reading! We may need to use multiple read() to read huge files.
  while ((nread < fileSize) && ((n = read(fd, &buffer[nread], fileSize-nread)) > 0)) {
  	nread += n;
	//n = read(fd, &buffer[nread], fileSize-nread);
  }
  	
  if (n < 0) {
		perror("File read error.");
		exit(EXIT_FAILURE);
  	}
  */

  clock_t start = clock();

  pthread_t thread;

  uint32_t n = 0;

  pthread_create(&thread, NULL, child, (void *) n);

  void *ptr;
  pthread_join(thread, &ptr);

  // calculate hash value of the whole input file as one big block!
  // uint32_t hash = jenkins_one_at_a_time_hash(buffer, fileSize);
  clock_t end = clock();
  printf("hash value = %u \n", (uint32_t) ptr);
  printf("time taken = %f \n", (end - start) * 1.0 / CLOCKS_PER_SEC);
  close(fd);
  return EXIT_SUCCESS;
}


uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, uint64_t length) 
{
  uint64_t i = 0;
  uint32_t hash = 0;

  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}


void usage(char* s) 
{
  fprintf(stderr, "Usage: %s filename num_threads\n", s);
  exit(EXIT_FAILURE);
}

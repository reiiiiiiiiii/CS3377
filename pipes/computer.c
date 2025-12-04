#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int low=1, high=100;

	while (low <= high) {
		//compute midpoint, send it to child and wait for response.
		int mid = (low + high)/2;
		fprintf(stderr, "mid: %d\n", mid);
		write(1, &mid, sizeof(int));

		char response;
		read(0, &response, 1);

		if (response == '<')
			high = mid-1;
		else if (response == '>')
			low = mid+1;
		else if (response == '=') {
			fputs("Great game!\n", stderr);
			break;
		} else
			fprintf (stderr, "Bad char %c\n", response);
	}
}


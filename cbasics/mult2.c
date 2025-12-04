#include <stdio.h>

int main() {
	int num = 0;
	printf("Enter number: ");
	scanf("%d", &num);

	for(int i = 1; i <= 10; i++) {
		printf("%4d & %2d = %7d\n", num, i, num*i);
		
	}
}

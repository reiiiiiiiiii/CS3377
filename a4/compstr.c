#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
	char str1[100];
	char str2[100];

	printf("Enter first string: ");
	fgets(str1, sizeof(str1), stdin);
	printf("Enter second string: ");
	fgets(str2, sizeof(str2), stdin);
	
	str1[strlen(str1)] = '\0';
	str2[strlen(str2)] = '\0';

	int i = 0;
	int j = 0;
	while(str1[i] != '\0' || str2[j] != '\0') {
		while(str1[i] != '\0' && isspace(str1[i])) i++;
		while(str2[j] != '\0' && isspace(str2[j])) j++;

		if(str1[i] == '\0' && str2[j] == '\0') {
			printf("Both strings are same\n");
			return 0;
		}

		if(tolower(str1[i]) != tolower(str2[j])) {
			printf("Both strings are different\n");
			return 0;
		}

		i++;
		j++;
	}

	printf("Both strings are same\n");
	return 0;
}

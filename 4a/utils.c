#include <stdio.h>
#include <stdlib.h>

int readUnsInteger(char *prompt, int *result) {
	int status = 0;

	printf("%s\n", prompt);
	while (status != 1) {
		status = scanf("%d", result);
		if (status < 0) {
			printf("end of file detected. exiting!\n");
			status = 0;
			break;
		} else if (status < 1) {
			printf("invalid input. try again!\n");
		}
		scanf("%*[^\n]");
	}

	return status;
}

unsigned int genUnsInteger(){
	return rand() % 101;
} 

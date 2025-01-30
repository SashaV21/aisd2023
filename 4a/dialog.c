#include <stdio.h>

#include "utils.h"

int dialog(const char *msgs[], const int N) {
	int option;

	for(int i = 0; i < N; i++)
		printf("%s\n", msgs[i]);

	if (!readUnsInteger("enter option: ", &option)) {
		option = 0;
	}

	while(option < 0 || option > N){
		printf("illegal input. try again\n");
		if (!readUnsInteger("enter option: ", &option)) {
			option = 0;
		}
	}

	return option;
}

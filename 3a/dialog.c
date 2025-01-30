#include <stdio.h>

#include "utils.h"

int dialog(const char *msgs[], const int N){
	for(int i = 0; i < N; i++)
		printf("%s\n", msgs[i]);
	int rc = 0;
	int res = getInt(&rc, "ENTER CHOISE -->");
	while(rc > N && res != 0){
		printf("WRONG CHOISE\n");
		res = getInt(&rc ,"ENTER CHOISE -->");
	}
	if(res == 0){
		return -1;
	}
	return rc;
}

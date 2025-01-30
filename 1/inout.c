#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void calloc_error(){
	printf("Calloc is not correct\n");
}

void validate(int *checking_value){
	while(scanf("%d", checking_value) == 0){
		printf("Value is not correct, please, try again. Enter value: ");
		scanf("%*[^\n]");		
	}
}

int *input_start_sequence(int *start_sequence_len){
	printf("Enter the length of start sequence: ");
	validate(start_sequence_len);
	if((*start_sequence_len) < 0){
		printf("Value is not correct, this number cannot be entered!\n ");
		// validate(start_sequence_len);
	}

	int *local_array = calloc((*start_sequence_len), sizeof(int));
	if(!local_array){
		return NULL;
	}
	for(int i = 0; i < (*start_sequence_len); i++){
		printf("Enter %d element of sequence: ", i);
		validate(&local_array[i]);
		if(local_array[i]  <= 0){
			printf("Value is not correct, this number cannot be entered!\n ");
			// validate(&local_array[i]);
		}
	}
	return local_array;
}

void print_start_sequence(const int *start_sequence, const int start_sequence_len){
	for(int i = 0; i < start_sequence_len; i++){
		printf("%d ", start_sequence[i]);
	}
	printf("\n");
}

void print_matrix(Matrix matrix){
	for(int i = 0; i < matrix.matrix_size; i++){
		printf("%d line: ", i);
		for(int j = 0; j < matrix.array_of_lines[i].line_size; j++ ){
			printf("%d ",  matrix.array_of_lines[i].array_in_line[j]);
		}
		printf("\n");
	}
}

#include <stddef.h>
#include "inout.h"
#include "general.h"
#include "cleaning.h"
#include "structs.h"

int main(){
	//input process
	int start_sequence_len = 0, *start_sequence = input_start_sequence(&start_sequence_len);
	// if(start_sequence == NULL){
		// calloc_error();
		// return 1;
	// }
	//general process
	Matrix matrix = general_process(start_sequence, start_sequence_len);
	if(matrix.array_of_lines == NULL) return 1;
	//output process
	print_start_sequence(start_sequence, start_sequence_len);
	print_matrix(matrix);
	//cleaning process
	clean_start_sequence(start_sequence);
	clean_matrix(matrix);
	return 0;
}

/*
	input and output processes are in inout.c
	general process is in general.c
	cleaning process is in cleaning.c
	structs decloration is in structs.h
*/

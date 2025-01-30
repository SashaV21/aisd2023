#include <stdlib.h>
#include "structs.h"

void clean_start_sequence(int *start_sequence){
	free(start_sequence);
}

void clean_matrix(Matrix matrix){
	for(int i = 0; i < matrix.matrix_size; i++){
		free(matrix.array_of_lines[i].array_in_line);
	}
	free(matrix.array_of_lines);
}

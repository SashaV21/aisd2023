#include <stdio.h>
#include <stdlib.h>
#include "inout.h"
#include "structs.h"

int calc_fib_number(const int first_num, const int second_num){
	return first_num + second_num;
}

int find_max_fib_number(const int input_num){
	int fib_first = 0, fib_second = 1, fib_n = 0;
	while(input_num > fib_n){
		fib_n = calc_fib_number(fib_first, fib_second);
		fib_first = fib_second;
		fib_second = fib_n;
	} 
	if (fib_n!=input_num) return fib_first;
	return fib_n;
}

int *calc_fib_decomposition(int input_num, int *decomposition_len){
	int *local_array = calloc(0, sizeof(int)), local_array_len = 0;
	while(input_num > 0){
		int max_fib_num = find_max_fib_number(input_num);
		local_array_len+=1;
		local_array = realloc(local_array, local_array_len * sizeof(int));
		local_array[local_array_len - 1] = max_fib_num;
		input_num -= max_fib_num;
	}
	(*decomposition_len) = local_array_len;
	return local_array;
}

Line do_line(int input_num){
	int decomp_len = 0;
	int *decomp = NULL;
	if(input_num > 0){
		decomp = calc_fib_decomposition(input_num, &decomp_len);		
	}
	Line line = {decomp_len, decomp};
	return line; 	
}

Matrix general_process(int *start_sequence, int start_sequence_len){
		Matrix matrix = {start_sequence_len, calloc(start_sequence_len, sizeof(Line))};
		for(int i = 0; i < start_sequence_len; i++){
			matrix.array_of_lines[i] = do_line(start_sequence[i]);
		}
		return matrix;
}



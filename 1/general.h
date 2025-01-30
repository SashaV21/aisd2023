#ifndef GENERAL_H
#define GENERAL_H
#include "structs.h"

int calc_fib_number(const int first_num, const int second_num);
int find_max_fib_number(const int input_num);
int *calc_fib_decomposition(int input_num, int *decomposition_len);
Line do_line(int input_num);
Matrix general_process(int *start_sequence, int start_sequence_len);

#endif

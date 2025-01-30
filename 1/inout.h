#ifndef INOUT_H
#define INOUT_H
#include "structs.h"

void calloc_error();
void validate(int *cheaking_value);
int *input_start_sequence(int *start_sequence_len);
void print_start_sequence(const int *start_sequence, const int start_sequence_len);
void print_matrix(Matrix matrix);

#endif

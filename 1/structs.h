#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Line{
	int line_size;
	int *array_in_line;
} Line;

typedef struct Matrix{
	int matrix_size;
	Line *array_of_lines;
} Matrix;

#endif

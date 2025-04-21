#pragma once

#include "../s21_matrix.h"
#include "base.h"

// int resize_result(int rows, int cols, matrix_t *result);
int check_matrix_arthmetics(matrix_t *a, matrix_t *b, matrix_t *result,
                            int is_mul);
void print_matrix(matrix_t *a);
int check_matrix(matrix_t *m);
void copy_matrix(matrix_t *a, matrix_t *b);
void get_minor(matrix_t *a, int row, int col, matrix_t *minor);
double wtime();
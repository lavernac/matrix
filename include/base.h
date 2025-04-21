#pragma once
#include "../s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

void print_matrix(matrix_t *a);
int check_matrix(matrix_t *m);

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);
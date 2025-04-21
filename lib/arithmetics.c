#include "../include/arithmetics.h"

#include <math.h>
#include <stdio.h>

#include "../include/helpers.h"

int s21_sum_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret_status = check_matrix_arthmetics(a, b, result, 0);
  if (ret_status) return ret_status;

  ret_status = s21_create_matrix(a->rows, a->columns, result);

  if (!ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++)
        result->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];

  return ret_status;
}

int s21_sub_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret_status = check_matrix_arthmetics(a, b, result, 0);
  if (ret_status) return ret_status;

  ret_status = s21_create_matrix(a->rows, a->columns, result);

  if (!ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++)
        result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];

  return ret_status;
}

int s21_mult_number(matrix_t *a, double number, matrix_t *result) {
  if (check_matrix(a) || !result) return INCORRECT_MATRIX_ERROR;
  if (!isfinite(number)) return CALC_ERROR;

  int ret_status = OK;
  ret_status = s21_create_matrix(a->rows, a->columns, result);

  if (!ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++) {
        if (isfinite(a->matrix[i][j]))
          result->matrix[i][j] = a->matrix[i][j] * number;
        else
          ret_status = CALC_ERROR;
      }
  return ret_status;
}

double calculate_cell_for_mul(matrix_t *a, matrix_t *b, int row, int col) {
  double sum = 0.0;

  for (int k = 0; k < a->columns; k++) {
    sum += a->matrix[row][k] * b->matrix[k][col];
  }
  return sum;
}

int s21_mult_matrix(matrix_t *a, matrix_t *b, matrix_t *result) {
  int ret_status = check_matrix_arthmetics(a, b, result, 1);
  if (ret_status) return ret_status;

  ret_status = s21_create_matrix(a->rows, b->columns, result);

  if (!ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < b->columns; j++)
        result->matrix[i][j] = calculate_cell_for_mul(a, b, i, j);

  return ret_status;
}
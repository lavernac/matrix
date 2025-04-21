#include "../include/helpers.h"

#include <math.h>
#include <stdio.h>

// void print_matrix(matrix_t *a) {
//   for (int i = 0; i < a->rows; i++) {
//     for (int j = 0; j < a->columns; j++) printf("%lf ", a->matrix[i][j]);
//     printf("\n");
//   }
//   printf("\n");
// }

int check_matrix(matrix_t *m) {
  int ret_status = OK;
  if (!m || m->rows <= 0 || m->columns <= 0 || !m->matrix)
    ret_status = INCORRECT_MATRIX_ERROR;

  // for (int i = 0; i < m->rows && !ret_status; i++)
  //   if (!m->matrix[i]) ret_status = INCORRECT_MATRIX_ERROR;

  return ret_status;
}

int check_matrix_arthmetics(matrix_t *a, matrix_t *b, matrix_t *result,
                            int is_mul) {
  int ret_status = OK;
  if (check_matrix(a) || check_matrix(b) || !result)
    ret_status = INCORRECT_MATRIX_ERROR;

  if (!ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++)
        if (!isfinite(a->matrix[i][j])) ret_status = CALC_ERROR;

  if (!ret_status)
    for (int i = 0; i < b->rows; i++)
      for (int j = 0; j < b->columns; j++)
        if (!isfinite(b->matrix[i][j])) ret_status = CALC_ERROR;

  if (!is_mul && !ret_status) {
    if (a->columns != b->columns || a->rows != b->rows) ret_status = CALC_ERROR;
  } else if (is_mul && !ret_status)
    if (a->columns != b->rows) ret_status = CALC_ERROR;

  return ret_status;
}

int resize_result(int rows, int cols, matrix_t *result) {
  s21_remove_matrix(result);
  return s21_create_matrix(rows, cols, result);
}

// void copy_matrix(matrix_t *a, matrix_t *b) {
//   b->columns = a->columns;
//   b->rows = a->rows;
//   for (int i = 0; i < a->rows; i++)
//     for (int j = 0; j < a->columns; j++) b->matrix[i][j] = a->matrix[i][j];
// }

void get_minor(matrix_t *a, int row, int col, matrix_t *minor) {
  if (a->rows - 1 > 0 && a->columns - 1 > 0) {
    resize_result(a->rows - 1, a->columns - 1, minor);
    for (int i = 0, i_m = 0; i < a->rows; i++, i_m++) {
      if (i == row) i++;
      for (int j = 0, j_m = 0; j < a->columns; j++, j_m++) {
        if (j == col) j++;
        if (i < a->rows && j < a->columns)
          minor->matrix[i_m][j_m] = a->matrix[i][j];
      }
    }
  }
}
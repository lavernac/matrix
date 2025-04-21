#include "../include/base.h"

#include <math.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (!result || rows <= 0 || columns <= 0) return INCORRECT_MATRIX_ERROR;

  int ret_status = OK;
  result->rows = rows;
  result->columns = columns;

  result->matrix = calloc(rows, sizeof(double *));

  if (result->matrix) {
    for (int i = 0; i < rows && !ret_status; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) ret_status = INCORRECT_MATRIX_ERROR;
    }
  }

  return ret_status;
}

void s21_remove_matrix(matrix_t *a) {
  if (a && a->matrix) {
    for (int i = 0; i < a->rows; i++)
      if (a->matrix[i]) {
        free(a->matrix[i]);
        a->matrix[i] = NULL;
      }
    free(a->matrix);
    a->columns = 0;
    a->rows = 0;
    a->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *a, matrix_t *b) {
  if (check_matrix(a) || check_matrix(b)) return FAILURE;

  int ret_status = SUCCESS;
  if (a->columns != b->columns || a->rows != b->rows) ret_status = FAILURE;

  if (ret_status)
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++)
        if (fabs(a->matrix[i][j] - b->matrix[i][j]) > 1e-7)
          ret_status = FAILURE;

  return ret_status;
}

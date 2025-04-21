#include "../include/matrix_operations.h"

#include <math.h>

#include "../include/helpers.h"

int s21_transpose(matrix_t *a, matrix_t *result) {
  if (check_matrix(a) || !result) return INCORRECT_MATRIX_ERROR;

  int ret_status = OK;
  ret_status = s21_create_matrix(a->columns, a->rows, result);

  if (!ret_status) {
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++)
        result->matrix[j][i] = a->matrix[i][j];
  }
  return ret_status;
}

int s21_calc_complements(matrix_t *a, matrix_t *result) {
  if (check_matrix(a) || !result)
    return INCORRECT_MATRIX_ERROR;
  else if (a->columns != a->rows)
    return CALC_ERROR;

  int ret_status = OK;
  matrix_t minor = {0};
  ret_status = s21_create_matrix(a->rows, a->columns, result);
  if (!ret_status) {
    double cell_value = 0.0;
    for (int i = 0; i < a->rows; i++)
      for (int j = 0; j < a->columns; j++) {
        get_minor(a, i, j, &minor);
        s21_determinant(&minor, &cell_value);
        result->matrix[i][j] = cell_value * pow(-1, i + j);
      }
  }
  s21_remove_matrix(&minor);
  return ret_status;
}

int s21_determinant(matrix_t *a, double *result) {
  if (check_matrix(a))
    return INCORRECT_MATRIX_ERROR;
  else if (a->columns != a->rows || !result)
    return CALC_ERROR;

  int ret_status = OK;
  if (a->rows == 1)
    *result = a->matrix[0][0];
  else if (a->rows == 2)
    *result =
        a->matrix[0][0] * a->matrix[1][1] - a->matrix[1][0] * a->matrix[0][1];
  else {
    matrix_t minor = {0};
    *result = 0.0;
    double res_tmp = 0.0;
    for (int i = 0; i < a->columns; i++, (*result) += res_tmp) {
      get_minor(a, 0, i, &minor);
      s21_determinant(&minor, &res_tmp);
      res_tmp *= a->matrix[0][i] * pow(-1, i);
    }
    s21_remove_matrix(&minor);
  }
  return ret_status;
}

int s21_inverse_matrix(matrix_t *a, matrix_t *result) {
  if (check_matrix(a) || !result) return INCORRECT_MATRIX_ERROR;
  double determinant = 0.0;
  s21_determinant(a, &determinant);
  if (determinant == 0.0 || a->rows != a->columns) return CALC_ERROR;

  int ret_status = OK;
  if (a->rows == 1 && !ret_status) {
    ret_status = s21_create_matrix(a->rows, a->columns, result);
    result->matrix[0][0] = 1 / determinant;
  } else if (!ret_status) {
    matrix_t tmp_m = {0}, tmp_transp = {0};
    if (!ret_status) {
      s21_calc_complements(a, &tmp_m);
      s21_transpose(&tmp_m, &tmp_transp);
      s21_mult_number(&tmp_transp, 1 / determinant, result);
    }

    s21_remove_matrix(&tmp_m);
    s21_remove_matrix(&tmp_transp);
  }
  return ret_status;
}
#include <stdio.h>

#include "../s21_matrix.h"

int main() {
  matrix_t m, check;
  s21_create_matrix(20000, 20000, &m);
  s21_create_matrix(20000, 20000, &check);
  // check.columns = 1;
  // check.rows = 1;
  // check.matrix = 0;
  // ck_assert_int_eq(
  double t = wtime();
  s21_sum_matrix(&m, &m, &check);
  t = wtime() - t;
  printf("Elapsed time: %lf\n", t);
  // , OK);
  // print_matrix(&m);
  // print_matrix(&check);
  // ck_assert_int_eq(s21_eq_matrix(&m, &check), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&check);
}
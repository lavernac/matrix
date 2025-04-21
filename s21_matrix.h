#pragma once

#define OK 0
#define INCORRECT_MATRIX_ERROR 1
#define CALC_ERROR 2

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

#include "include/arithmetics.h"
#include "include/base.h"
#include "include/helpers.h"
#include "include/matrix_operations.h"
#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int res = INCORRECT;

  if (!(rows > 0 && columns > 0)) {
    return ERR;
  }

  result->matrix = (double**)calloc(rows, sizeof(double*));
  if (!result->matrix) {
    return ERR;
  }

  for (int i = 0; i < rows; i += 1) {
    result->matrix[i] = (double*)calloc(columns, sizeof(double));
    if (!result->matrix[i]) {
      for (int j = 0; j < i; j += 1) free(result->matrix[j]);
      free(result->matrix);
      return ERR;
    }
    for (int k = 0; k < columns; k += 1) {
      result->matrix[i][k] = 0;
    }
  }

  result->columns = columns;
  result->rows = rows;
  res = OK;

  return res;
}

void s21_remove_matrix(matrix_t* A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i += 1) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_check_matrix_inputs(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return ERR;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    return ERR;
  }

  return OK;
}

int s21_square_matrix(matrix_t* A) {
  int res = OK;
  if (A->rows != A->columns) {
    res = ERR;
  }
  return res;
}

int s21_is_null_matrix(matrix_t* A) {
  int res = OK;
  if (A->matrix == NULL) {
    res = INCORRECT;
  }
  return res;
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  if (A == NULL || B == NULL || A->rows != B->rows ||
      A->columns != B->columns) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double A_integer, A_fract;
      double B_integer, B_fract;

      A_fract = modf(A->matrix[i][j], &A_integer);
      B_fract = modf(B->matrix[i][j], &B_integer);

      if (A_integer != B_integer || !s21_compare_parts(A_fract, B_fract)) {
        return FAILURE;
      }
    }
  }

  return SUCCESS;
}

int s21_compare_parts(double a, double b) {
  int k = 0;
  int result = SUCCESS;

  while (k < 7 && result == SUCCESS) {
    a *= 10;
    b *= 10;
    double a_integer;
    double b_integer;
    modf(a, &a_integer);
    modf(b, &b_integer);

    if (a_integer != b_integer) {
      result = FAILURE;
    }

    k++;
  }

  return result;
}

int s21_transpose(matrix_t* A, matrix_t* result) {
  int res = s21_is_null_matrix(A);

  if (res != OK) {
    return res;
  }

  res = s21_create_matrix(A->columns, A->rows, result);
  if (res != OK) {
    return res;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}
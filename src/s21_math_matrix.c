#include "s21_matrix.h"

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (s21_is_null_matrix(A) != OK || s21_is_null_matrix(B) != OK) {
    return INCORRECT;
  }

  int check = s21_check_matrix_inputs(A, B, result);
  if (check != OK) {
    return check;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (s21_is_null_matrix(A) != OK || s21_is_null_matrix(B) != OK) {
    return INCORRECT;
  }

  int check = s21_check_matrix_inputs(A, B, result);
  if (check != OK) {
    return check;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int check = s21_is_null_matrix(A);

  if (check != OK) {
    return INCORRECT;
  }

  check = s21_create_matrix(A->rows, A->columns, result);
  if (check != OK) {
    return check;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return OK;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int checkA = s21_is_null_matrix(A);
  int checkB = s21_is_null_matrix(B);

  if (checkA != OK || checkB != OK) {
    return INCORRECT;
  }

  if (A->columns != B->rows) {
    return ERR;
  }

  int checkCreate = s21_create_matrix(A->rows, B->columns, result);
  if (checkCreate != OK) {
    return checkCreate;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}
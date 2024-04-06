#include "s21_matrix.h"

int s21_determinant(matrix_t* A, double* result) {
  int res = s21_is_null_matrix(A);

  if (res != OK) {
    return res;
  }

  res = s21_square_matrix(A);

  if (res != OK) {
    return res;
  }

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  if (A->rows == 2) {
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]);
    return OK;
  }

  *result = s21_complement_of_first_row(A, &res);
  return res;
}
int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int res = s21_is_null_matrix(A);

  if (res != OK) {
    return res;
  }

  res = s21_square_matrix(A);

  if (res != OK) {
    return res;
  }

  matrix_t buffer = {0};
  res = s21_create_matrix(A->rows, A->columns, result);

  if (res != OK) {
    return res;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      res = s21_create_matrix(A->rows - 1, A->columns - 1, &buffer);

      if (res != OK) {
        s21_remove_matrix(result);
        return INCORRECT;
      }

      s21_matrix_filling(A, i, j, &buffer);
      s21_determinant(&buffer, &(result->matrix[i][j]));

      if (((i + j) % 2) != 0) {
        result->matrix[i][j] *= -1;
      }

      s21_remove_matrix(&buffer);
    }
  }

  return OK;
}
void s21_matrix_filling(matrix_t* A, int rows, int columns, matrix_t* result) {
  int q = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != rows) {
      for (int j = 0, k = 0; j < A->columns; j++) {
        if (j != columns) {
          result->matrix[q][k] = A->matrix[i][j];
          k++;
        }
      }
      q++;
    }
  }
}

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  int res = s21_is_null_matrix(A);

  if (res != OK) {
    return res;
  }

  res = s21_create_matrix(A->columns, A->rows, result);

  if (res != OK) {
    return res;
  }

  matrix_t buffer1 = {0};
  s21_calc_complements(A, &buffer1);
  matrix_t buffer2 = {0};
  s21_transpose(&buffer1, &buffer2);

  double det = 0;
  res = s21_determinant(A, &det);

  if (res == OK && det == 0) {
    res = 2;
  }

  if (res == OK) {
    for (int i = 0; i < buffer2.rows; i++) {
      for (int j = 0; j < buffer2.columns; j++) {
        result->matrix[i][j] = buffer2.matrix[i][j] / det;
      }
    }
  }

  s21_remove_matrix(&buffer2);
  s21_remove_matrix(&buffer1);

  return res;
}

double s21_complement_of_first_row(matrix_t* A, int* check) {
  double result = 0;
  double ch_buffer = 0;
  matrix_t buffer = {0};
  for (int i = 0; i < A->columns && *check == OK; i++) {
    *check = s21_create_matrix(A->rows - 1, A->columns - 1, &buffer);
    if (*check == OK) {
      s21_matrix_filling(A, 0, i, &buffer);
      *check = s21_determinant(&buffer, &ch_buffer);
      if ((i % 2) != 0) {
        ch_buffer *= -1;
      }
      result += ch_buffer * A->matrix[0][i];
    } else {
      *check = INCORRECT;
    }
    s21_remove_matrix(&buffer);
  }
  return result;
}
#include "matrix.h"

matrix_t init_matrix(int rows, int collumns) {
  matrix_t m;
  m.rows = rows;
  m.collumns = collumns;

  m.data =
      (matrix_data_t **)malloc((unsigned long)rows * sizeof(matrix_data_t *));

  for (int i = 0; i < m.rows; i++) {
    m.data[i] = (matrix_data_t *)malloc((unsigned long)collumns *
                                        sizeof(matrix_data_t));
  }

  return m;
}

void read_matrix_data(matrix_t *m, FILE *file) {
  for (int i = 0; i < m->rows; i++)
    for (int j = 0; j < m->collumns; j++)
      if (fscanf(file, "%d", &m->data[i][j]) != 1) {
        printf("Invalid input\n");
        exit(1);
      }
}

void print_matrix(matrix_t *m, FILE *file) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->collumns; j++) {
      fprintf(file, "%d ", m->data[i][j]);
    }
    fprintf(file, "\n");
  }
}

void free_matrix(matrix_t *m) {
  for (int i = 0; i < m->rows; i++) {
    free(m->data[i]);
  }
  free(m->data);
}

matrix_data_t sum_above_primary_diagonal(matrix_t *m) {
  matrix_data_t sum = 0;

  for (int i = 0; i < m->rows; i++)
    for (int j = i + 1; j < m->collumns; j++)
      sum += m->data[i][j];

  return sum;
}

matrix_data_t sum_below_secondary_diagonal(matrix_t *m) {
  matrix_data_t sum = 0;

  for (int i = 0; i < m->rows; i++)
    for (int j = 0; j < i; j++)
      sum += m->data[i][j];

  return sum;
}

matrix_data_t quadrant_sum(matrix_t *m, int option) {

  matrix_data_t sum = 0;

  // primary upper -> i < j
  // primary lower -> i > j
  // secondary upper -> i + j < n - 1
  // secondary lower -> i + j > n - 1
  // 1 -> top -> i < j && i + j < n - 1
  // 2 -> right -> i < j && i + j > n - 1
  // 3 -> bottom -> i > j && i + j > n - 1
  // 4 -> left -> i > j && i + j < n - 1

  switch (option) {
  case 1:
    for (int i = 0; i < m->rows; i++)
      for (int j = i + 1; j < m->rows; j++)
        if (i + j < m->rows - 1)
          sum += m->data[i][j];
    break;
  case 2:
    for (int i = 0; i < m->rows; i++)
      for (int j = i + 1; j < m->rows; j++)
        if (i + j > m->rows - 1)
          sum += m->data[i][j];
    break;
  case 3:
    for (int i = 0; i < m->rows; i++)
      for (int j = 0; j < i; j++)
        if (i + j > m->rows - 1)
          sum += m->data[i][j];
    break;
  case 4:
    for (int i = 0; i < m->rows; i++)
      for (int j = 0; j < i; j++)
        if (i + j < m->rows - 1)
          sum += m->data[i][j];
    break;
  default:
    printf("Invalid option\n");
    break;
  }
  return sum;
}

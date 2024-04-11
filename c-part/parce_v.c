#include "backend.h"

double *parsing_v(char *temp) {
  double *arr = (double *)calloc(3, sizeof(double));
  if (arr != NULL) {
    unsigned int poz = 0;
    while (temp[0] != '\n' && temp[0] != '\r' && (int)temp[0] != 0) {
      arr[poz] = (int)strtod(temp, &temp);
      poz++;
    }
  }
  return arr;
}

void v_process(char *str, matrix_t *point, int row) {
  char *right_str = &str[2];
  double *array_of_values = parsing_v(right_str);
  for (int i = 0; i < 3; i++) {
    point->matrix[row][i] = array_of_values[i];
  }
  free(array_of_values);
}

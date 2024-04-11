#include "backend.h"

void allocate_memory(data *point) {
  point->error +=
      create_matrix(point->count_of_vertexes + 1, 3, &point->vertexes);
  point->error += create_facets(point);
}

void remove_memory(data *point) {
  if (point->count_of_vertexes != 0)
    remove_matrix(point->vertexes);
  if (point->facets != NULL)
    remove_facets(point);
}

int create_matrix(unsigned int rows, unsigned int cols, matrix_t **result) {
  int answer = 0;
  if (*result == NULL) {
    *result = (matrix_t *)malloc(sizeof(matrix_t));
    (*result)->rows = rows;
    (*result)->cols = cols;
  } else {
    remove_matrix(*result);
    *result = (matrix_t *)malloc(sizeof(matrix_t));
    (*result)->rows = rows;
    (*result)->cols = cols;
  }
  if (*result != NULL) {
    (*result)->matrix = (double **)calloc(rows, sizeof(double *));
    if ((*result)->matrix != NULL) {
      for (unsigned int i = 0; i < rows; i++) {
        (*result)->matrix[i] = (double *)calloc(cols, sizeof(double));
        if ((*result)->matrix[i] == NULL) {
          answer = 1;
          break;
        }
      }
    } else {
      answer = 1;
    }
  } else {
    answer = 1;
  }
  return answer;
}

void remove_matrix(matrix_t *point) {
  for (unsigned int i = 0; i < point->rows; i++) {
    free(point->matrix[i]);
  }
  free(point->matrix);
  free(point);
  point = NULL;
}

int create_facets(data *point) {
  int error = 1;
  point->facets = calloc(point->count_of_vertexes_in_facets, sizeof(int));
  if (point->facets != NULL) {
    error = 0;
  }
  return error;
}

void remove_facets(data *point) { free(point->facets); }

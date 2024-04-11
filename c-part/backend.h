#ifndef SRC_BACKEND_H_
#define SRC_BACKEND_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix_struct {
  double **matrix;
  unsigned int rows;
  unsigned int cols;
} matrix_t;

typedef struct data {
  const char *file_name;
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  unsigned int count_of_vertexes_in_facets;
  matrix_t *vertexes;
  int *facets;
  int error;
} data;

// Memory allocate
int create_matrix(unsigned int rows, unsigned int cols, matrix_t **result);
void remove_matrix(matrix_t *point);
int create_facets(data *point);
void remove_facets(data *point);
void allocate_memory(data *point);
void remove_memory(data *point);

// Main functions
void __init__data(data *point);
void explore_the_file(data *point);
void get_data_from_file(data *point);
double *make_right_vert(matrix_t *point);
int *make_right_index(data *point, int size);
int vertInFacetsCounting(char *str);

// Parsing V from file
void v_process(char *str, matrix_t *point, int row);
void fulling_matrix(char *temp, matrix_t *matrix_v, int v_count);

// Parsing F from file
int *parsing_f(char *temp, int size);
void f_process(data *point, char *str, int **facets, int size, int *poz);

// Аффинные преобразования
void translation_X(matrix_t **mat, double x);
void translation_Y(matrix_t **mat, double y);
void translation_Z(matrix_t **mat, double z);
void rotation_X(matrix_t **mat, double x);
void rotation_Y(matrix_t **mat, double y);
void rotation_Z(matrix_t **mat, double z);
void scale_m(matrix_t **mat, double s);
#endif // SRC_BACKEND_H_

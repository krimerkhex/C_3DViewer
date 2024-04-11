#include "backend.h"

void __init__data(data *point) {
  point->count_of_facets = 0;
  point->count_of_vertexes = 0;
  point->count_of_vertexes_in_facets = 0;
  point->error = 0;
  point->vertexes = NULL;
  point->facets = NULL;
}

void explore_the_file(data *point) {
  FILE *file = NULL;
  if ((file = fopen(point->file_name, "r")) != NULL) {
    char *str = calloc(sizeof(char), 128);
    if (str != NULL) {
      while (fgets(str, 128, file) != NULL) {
        if ((int)strlen(str) >= 2) {
          if (str[0] == 'f' && str[1] == ' ') {
            (point->count_of_facets)++;
            point->count_of_vertexes_in_facets += vertInFacetsCounting(str) * 2;
          }
          if (str[0] == 'v' && str[1] == ' ') {
            (point->count_of_vertexes)++;
          }
        }
      }
      free(str);
      fclose(file);
    } else {
      point->error = 1;
    }
  } else {
    point->error = 1;
  }
}

void get_data_from_file(data *point) {
  FILE *file = NULL;
  if ((file = fopen(point->file_name, "r")) != NULL) {
    allocate_memory(point);
    char *temp = (char *)calloc(128, sizeof(char));
    if (!point->error && temp != NULL) {
      int temp_v = 0, temp_f = 0;
      while (fgets(temp, 128, file) != NULL && !point->error) {
        if ((int)strlen(temp) >= 2) {
          if (temp[0] == 'f' && temp[1] == ' ') {
            int size = vertInFacetsCounting(temp);
            f_process(point, temp, &point->facets, size, &temp_f);
          }
          if (temp[0] == 'v' && temp[1] == ' ') {
            v_process(temp, point->vertexes, temp_v);
            temp_v++;
          }
        }
      }
      free(temp);
      fclose(file);
    } else {
      point->error = 1;
      free(temp);
    }
  }
}

double *make_right_vert(matrix_t *point) {
  double *tmp = NULL;
  if (point != NULL) {
    if (point->cols != 0 && point->rows != 0) {
      tmp = calloc(point->cols * point->rows * 3, sizeof(double));
    }
    if (tmp != NULL && point != NULL) {
      int count = 0;
      for (unsigned int i = 0; i < point->rows; i++) {
        for (unsigned int j = 0; j < point->cols; j++) {
          tmp[count] = point->matrix[i][j];
          count++;
        }
      }
    }
  }
  return tmp;
}

int vertInFacetsCounting(char *str) {
  int count = 0;
  for (int i = 0; (int)str[i] != 0; i++) {
    if (str[i] == ' ' && (int)str[i + 1] >= 49 && (int)str[i + 1] <= 57) {
      count++;
    }
  }
  return count;
}

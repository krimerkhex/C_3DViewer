#include "backend.h"

int *parsing_f(char *temp, int size) {
  // printf("str = %s\n", temp);
  //  func(temp);
  //  printf("str = %s\n", temp);
  int *arr = calloc(size, sizeof(int));
  if (arr != NULL) {
    int poz = 0;
    for (int i = 0; i < size; i++) {
      arr[poz] = (int)strtoul(temp, &temp, 0);
      //        printf("str = %s\n", temp);
      poz++;
      // if (strlen(temp) > 3) {
      while (temp[0] != ' ') {
        if (i == size - 1) {
          break;
        }
        temp++;
      }
      // }
    }
  }

  return arr;
}

void f_process(data *point, char *str, int **facets, int size, int *poz) {
  char *right_str = &str[2];
  int *temp_array = parsing_f(right_str, size);
  if (temp_array != NULL) {
    for (int i = 0; i < size; i++) {
      if (i == 0) {
        (*facets)[*poz] = temp_array[i] - 1;
        (*facets)[*poz + (size * 2 - 1)] = temp_array[i] - 1;
        *poz += 1;
      } else {
        (*facets)[*poz] = temp_array[i] - 1;
        (*facets)[*poz + 1] = temp_array[i] - 1;
        *poz += 2;
      }
    }
    *poz += 1;
    free(temp_array);
  } else {
    point->error = 1;
  }
}

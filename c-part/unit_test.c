#include "backend.h"
#include <check.h>

void copy_matrix(matrix_t **dst, matrix_t **src) {
  for (unsigned int i = 0; i < (*src)->rows; i++) {
    for (unsigned int j = 0; j < (*src)->cols; j++) {
      (*dst)->matrix[i][j] = (*src)->matrix[i][j];
    }
  }
}

START_TEST(test_all_1) {
  struct data test_1;
  __init__data(&test_1);
  test_1.file_name = "../datasets/CUB.obj";
  explore_the_file(&test_1);
  ck_assert_int_eq(test_1.error, 0);
  if (!test_1.error) {
    get_data_from_file(&test_1);
  }
}

START_TEST(test_all_2) {
  struct data test_2;
  __init__data(&test_2);
  test_2.file_name = "../datasets/.obj";
  ck_assert_int_eq(test_2.error, 0);
}

START_TEST(test_all_3) {
  struct data* test_3 = (struct data*)calloc(sizeof(struct data), 1);
  if (test_3 != NULL) {
    __init__data(test_3);
    test_3->file_name = "../datasets/CUB.obj";
    explore_the_file(test_3);
    ck_assert_int_eq(test_3->error, 0);
    if (!test_3->error) {
      get_data_from_file(test_3);
      matrix_t* matrix = NULL;
      create_matrix(test_3->vertexes->rows, test_3->vertexes->cols, &matrix);
      copy_matrix(&matrix, &test_3->vertexes);
      double shift = 1;
      translation_X(&test_3->vertexes, shift);
      translation_Y(&test_3->vertexes, shift);
      translation_Z(&test_3->vertexes, shift);
      for (unsigned int i = 0; i < test_3->vertexes->rows; i++) {
        for (unsigned int j = 0; j < test_3->vertexes->cols; j++) {
          ck_assert_double_eq(test_3->vertexes->matrix[i][j] - shift,
                              matrix->matrix[i][j]);
        }
      }
      remove_matrix(matrix);
    }
    remove_memory(test_3);
    free(test_3);
  }
}

START_TEST(test_all_4) {
  struct data* test_4 = (struct data*)calloc(sizeof(struct data), 1);
  if (test_4 != NULL) {
    __init__data(test_4);
    test_4->file_name = "../datasets/CUB.obj";
    explore_the_file(test_4);
    ck_assert_int_eq(test_4->error, 0);
    if (!test_4->error) {
      get_data_from_file(test_4);
      matrix_t* matrix = NULL;
      if (!create_matrix(test_4->vertexes->rows, test_4->vertexes->cols, &matrix)) {
        copy_matrix(&matrix, &test_4->vertexes);
        double shift = 30.5;
        rotation_X(&test_4->vertexes, shift);
        rotation_Y(&test_4->vertexes, shift);
        rotation_Z(&test_4->vertexes, shift);
        rotation_X(&matrix, shift);
        rotation_Y(&matrix, shift);
        rotation_Z(&matrix, shift);
        for (unsigned int i = 0; i < test_4->vertexes->rows; i++) {
          for (unsigned int j = 0; j < test_4->vertexes->cols; j++) {
            ck_assert_double_eq(test_4->vertexes->matrix[i][j],
                                matrix->matrix[i][j]);
          }
        }        
        remove_matrix(matrix);
      }
    }
    remove_memory(test_4);
    free(test_4);
  }
}

START_TEST(test_all_5) {
  struct data* test_5 = (struct data*)calloc(sizeof(struct data), 1);
  if (test_5 != NULL) {
    __init__data(test_5);
    test_5->file_name = "../datasets/CUB.obj";
    explore_the_file(test_5);
    ck_assert_int_eq(test_5->error, 0);
    if (!test_5->error) {
      get_data_from_file(test_5);
      matrix_t* matrix = NULL;
      create_matrix(test_5->vertexes->rows, test_5->vertexes->cols, &matrix);
      copy_matrix(&matrix, &test_5->vertexes);
      double shift = 30.5;
      scale_m(&test_5->vertexes, shift);
      for (unsigned int i = 0; i < test_5->vertexes->rows; i++) {
        for (unsigned int j = 0; j < test_5->vertexes->cols; j++) {
          ck_assert_double_eq(test_5->vertexes->matrix[i][j] / shift,
                              matrix->matrix[i][j]);
        }
      }
      remove_matrix(matrix);
    }
    remove_memory(test_5);
    free(test_5);
  }
}

int main() {
  Suite *s1 = suite_create("s21_affint: ");
  TCase *tc1_1 = tcase_create("s21_affint: ");
  SRunner *sr = srunner_create(s1);
  int result;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_all_1);
  tcase_add_test(tc1_1, test_all_2);
  tcase_add_test(tc1_1, test_all_3);
  tcase_add_test(tc1_1, test_all_4);
  tcase_add_test(tc1_1, test_all_5);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}

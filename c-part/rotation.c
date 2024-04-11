#include "backend.h"

void translation_X(matrix_t **mat, double x) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++)
      (*mat)->matrix[i][0] += x;
  }
}

void translation_Y(matrix_t **mat, double y) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++)
      (*mat)->matrix[i][1] += y;
  }
}

void translation_Z(matrix_t **mat, double z) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++)
      (*mat)->matrix[i][2] += z;
  }
}

void rotation_X(matrix_t **mat, double x) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++) {
      double temp_y = (*mat)->matrix[i][1];
      double temp_z = (*mat)->matrix[i][2];
      (*mat)->matrix[i][1] = cos(x) * temp_y - sin(x) * temp_z;
      (*mat)->matrix[i][2] = sin(x) * temp_y + cos(x) * temp_z;
    }
  }
}

void rotation_Y(matrix_t **mat, double y) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++) {
      double temp_x = (*mat)->matrix[i][0];
      double temp_z = (*mat)->matrix[i][2];
      (*mat)->matrix[i][0] = temp_x * cos(y) + temp_z * sin(y);
      (*mat)->matrix[i][2] = -1 * temp_x * sin(y) + temp_z * cos(y);
    }
  }
}

void rotation_Z(matrix_t **mat, double z) {
  if (mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++) {
      double temp_y = (*mat)->matrix[i][1];
      double temp_x = (*mat)->matrix[i][0];
      (*mat)->matrix[i][0] = temp_x * cos(z) - temp_y * sin(z);
      (*mat)->matrix[i][1] = temp_x * sin(z) + temp_y * cos(z);
    }
  }
}

void scale_m(matrix_t **mat, double s) {
  if (s != 0. && mat != NULL) {
    for (unsigned int i = 0; i < (*mat)->rows; i++) {
      for (unsigned int j = 0; j < (*mat)->cols; j++) {
        (*mat)->matrix[i][j] *= s;
      }
    }
  }
}

#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#define GL_SILENCE_DEPRECATION
#include <QColorDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPoint>
#include <QPointerEvent>
#include <QWidget>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "../c-part/backend.h"
#ifdef __cplusplus
}
#endif

class graphicwindow : public QOpenGLWidget, QOpenGLFunctions {
public:
  graphicwindow(QWidget *parent = nullptr);

  double *vertex_array = NULL;
  int *indexes_array = NULL;
  const char *file_path = NULL;
  int edges_counter = 0;
  struct data file_data;
  int dots_counter = 0;
  void start_process();
  void update_process();
  int projection_type = 0;

  float *lines_color1 = (float *)calloc(3, sizeof(float));
  double rib_size1;
  float *back_color1 = (float *)calloc(4, sizeof(float));
  int line_type1;
  float *tops_color1 = (float *)calloc(3, sizeof(float));
  int display_tops1;
  double tops_size1;

  QColor rib_color;
  QColor vert_color;
  QColor back_color = QColor::fromRgbF(1, 0.5, 0.5);

  void change_lines_color();
  void change_back_color();
  void choose_line_type();
  void change_points();

  double shift = 0.05;

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

signals:
};

#endif // GRAPHICWINDOW_H

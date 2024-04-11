#include "graphicwindow.h"

graphicwindow::graphicwindow(QWidget *parent) : QOpenGLWidget{parent} {}

void graphicwindow::start_process() {
  __init__data(&file_data);
  file_data.file_name = file_path;
  explore_the_file(&file_data);
  if (!file_data.error) {
    get_data_from_file(&file_data);
  } else {
    remove_memory(&file_data);
  }
  vertex_array = make_right_vert(this->file_data.vertexes);
  indexes_array = file_data.facets;
  edges_counter = file_data.count_of_vertexes_in_facets;
  dots_counter = file_data.count_of_vertexes;
  update();
}

void graphicwindow::update_process() {
  vertex_array = make_right_vert(this->file_data.vertexes);
  update();
}

void graphicwindow::change_back_color() {
  if (back_color.isValid()) {
    back_color.getRgbF(&back_color1[0], &back_color1[1], &back_color1[2]);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(back_color1[0], back_color1[1], back_color1[2],
                    back_color1[3]);
    f->glClear(GL_COLOR_BUFFER_BIT);
  } else {
    glClearColor(back_color1[0], back_color1[1], back_color1[2],
                 back_color1[3]);
  }
}

void graphicwindow::choose_line_type() {
  if (line_type1 == 1) {
    glLineStipple(1, 0x3F07);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void graphicwindow::change_lines_color() {
  if (rib_color.isValid()) {
    rib_color.getRgbF(&lines_color1[0], &lines_color1[1], &lines_color1[2]);
    glColor3d(lines_color1[0], lines_color1[1], lines_color1[2]);
  } else {
    glColor3d(lines_color1[0], lines_color1[1], lines_color1[2]);
  }
}

void graphicwindow::change_points() {
  if (display_tops1 > 0) {
    glPointSize(tops_size1);
    glDisable(GL_POINT_SMOOTH);
    if (display_tops1 == 2) {
      glEnable(GL_POINT_SMOOTH);
    }
    if (vert_color.isValid()) {
      vert_color.getRgbF(&tops_color1[0], &tops_color1[1], &tops_color1[2]);
      glColor3d(tops_color1[0], tops_color1[1], tops_color1[2]);
    } else {
      glColor3d(tops_color1[0], tops_color1[1], tops_color1[2]);
    }
    glDrawElements(GL_POINTS, edges_counter, GL_UNSIGNED_INT, indexes_array);
  }
}

void graphicwindow::initializeGL() {
  initializeOpenGLFunctions();
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void graphicwindow::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void graphicwindow::paintGL() {
  change_back_color();
  if (projection_type == 0) {
    glOrtho(-1, 1, -1, 1, 1, 1000);
  } else if (projection_type == 1) {
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
  glTranslatef(0, 0, -4);
  glLineWidth(2);
  glBegin(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
  // lines
  change_lines_color();
  glVertexPointer(3, GL_DOUBLE, 0, vertex_array);
  choose_line_type();
  glLineWidth(rib_size1);
  glDrawElements(GL_LINES, edges_counter, GL_UNSIGNED_INT, indexes_array);

  // points
  change_points();
  glDisableClientState(GL_VERTEX_ARRAY);
  glEnd();
  update();
}

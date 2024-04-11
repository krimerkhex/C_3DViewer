#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gifimage/qgifimage.h"
#include "graphicwindow.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMainWindow>
#include <QMovie>
#include <QPushButton>
#include <QSettings>
#include <QSize>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

extern "C" {
#include "../c-part/backend.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Ui::MainWindow *ui;
  graphicwindow *openglview;
  QTimer *timer;
  void take_settings();
  void save_settings();

private slots:
  void on_choose_button_clicked();
  void shift();
  void rotation();
  void scale();

  void change_color();
  void change_lines_type();
  void change_rib_size();
  void change_tops_type();
  void change_tops_size();

  void set_start_settings();
  void make_gif();
  void make_screen();
  void on_screen_but_clicked();
  void on_gif_but_clicked();

  void on_proect_type_currentTextChanged(const QString &arg1);
};

#endif // MAINWINDOW_H

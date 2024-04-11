#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->widget->start_process();
  connect(ui->mov_x_min, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_x_plus, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_y_min, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_y_plus, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_z_min, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_z_plus, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->mov_z_plus, SIGNAL(clicked()), this, SLOT(shift()));
  connect(ui->rot_x_min, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->rot_x_plus, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->rot_y_min, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->rot_y_plus, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->rot_z_min, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->rot_z_plus, SIGNAL(clicked()), this, SLOT(rotation()));
  connect(ui->zoom_in, SIGNAL(clicked()), this, SLOT(scale()));
  connect(ui->zoom_out, SIGNAL(clicked()), this, SLOT(scale()));
  connect(ui->rib_color, SIGNAL(clicked()), this, SLOT(change_color()));
  connect(ui->vert_color, SIGNAL(clicked()), this, SLOT(change_color()));
  connect(ui->back_color, SIGNAL(clicked()), this, SLOT(change_color()));

  connect(ui->rib_type, SIGNAL(currentTextChanged(QString)), this,
          SLOT(change_lines_type()));
  connect(ui->rib_size, SIGNAL(valueChanged(int)), this,
          SLOT(change_rib_size()));

  connect(ui->vert_type, SIGNAL(currentTextChanged(QString)), this,
          SLOT(change_tops_type()));
  connect(ui->vert_size, SIGNAL(valueChanged(int)), this,
          SLOT(change_tops_size()));

  std::cout << "\n!!!!!!!";
}

MainWindow::~MainWindow() {
  save_settings();
  free(ui->widget->indexes_array);
  free(ui->widget->vertex_array);
  delete ui;
}

void MainWindow::on_choose_button_clicked() {
  QString str = QFileDialog::getOpenFileName(
      this, "Выбрать файл 3D модели", QDir::homePath(),
      "OBJ files (*.obj);; All files (*.*)");
  QByteArray tmp_filepath = str.toLocal8Bit();
  ui->widget->file_path = tmp_filepath.data();
  ui->widget->start_process();
  ui->file_path_label->setText(ui->widget->file_path);
  ui->f_count->setText(QString::number(ui->widget->file_data.count_of_facets));
  ui->v_count->setText(
      QString::number(ui->widget->file_data.count_of_vertexes));
}

void MainWindow::rotation() {
  double shift = 0.5;
  QPushButton *button = (QPushButton *)sender();
  if (ui->file_path_label->text().toStdString().length()) {
    if (button == ui->rot_x_plus) {
      ui->rot_x_value->setText(
          QString::number(ui->rot_x_value->text().toDouble() + shift));
      rotation_X(&ui->widget->file_data.vertexes, shift);

    } else if (button == ui->rot_x_min) {
      ui->rot_x_value->setText(
          QString::number(ui->rot_x_value->text().toDouble() - shift));
      rotation_X(&ui->widget->file_data.vertexes, -1 * shift);

    } else if (button == ui->rot_y_plus) {
      ui->rot_y_value->setText(
          QString::number(ui->rot_y_value->text().toDouble() + shift));
      rotation_Y(&ui->widget->file_data.vertexes, shift);

    } else if (button == ui->rot_y_min) {
      ui->rot_y_value->setText(
          QString::number(ui->rot_y_value->text().toDouble() - shift));
      rotation_Y(&ui->widget->file_data.vertexes, -1 * shift);

    } else if (button == ui->rot_z_plus) {
      ui->rot_z_value->setText(
          QString::number(ui->rot_z_value->text().toDouble() + shift));
      rotation_Z(&ui->widget->file_data.vertexes, shift);

    } else if (button == ui->rot_z_min) {
      ui->rot_z_value->setText(
          QString::number(ui->rot_z_value->text().toDouble() - shift));
      rotation_Z(&ui->widget->file_data.vertexes, -1 * shift);
    }
    free(ui->widget->vertex_array);
    ui->widget->vertex_array = make_right_vert(ui->widget->file_data.vertexes);
  }
}

void MainWindow::shift() {
  double shift = 0.05;
  QPushButton *button = (QPushButton *)sender();
  if (ui->file_path_label->text().toStdString().length()) {
    if (button == ui->mov_x_min) {
      ui->mov_x_value->setText(
          QString::number(ui->mov_x_value->text().toDouble() - shift));
      translation_X(&ui->widget->file_data.vertexes, -1 * shift);
    } else if (button == ui->mov_x_plus) {
      ui->mov_x_value->setText(
          QString::number(ui->mov_x_value->text().toDouble() + shift));
      translation_X(&ui->widget->file_data.vertexes, shift);
    } else if (button == ui->mov_y_min) {
      ui->mov_y_value->setText(
          QString::number(ui->mov_y_value->text().toDouble() - shift));
      translation_Y(&ui->widget->file_data.vertexes, -1 * shift);
    } else if (button == ui->mov_y_plus) {
      ui->mov_y_value->setText(
          QString::number(ui->mov_y_value->text().toDouble() + shift));
      translation_Y(&ui->widget->file_data.vertexes, shift);
    } else if (button == ui->mov_z_min) {
      ui->mov_z_value->setText(
          QString::number(ui->mov_z_value->text().toDouble() - shift));
      translation_Z(&ui->widget->file_data.vertexes, -1 * shift);
    } else if (button == ui->mov_z_plus) {
      ui->mov_z_value->setText(
          QString::number(ui->mov_z_value->text().toDouble() + shift));
      translation_Z(&ui->widget->file_data.vertexes, shift);
    }
    free(ui->widget->vertex_array);
    ui->widget->vertex_array = make_right_vert(ui->widget->file_data.vertexes);
  }
}

void MainWindow::scale() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->zoom_in) {
    scale_m(&ui->widget->file_data.vertexes, 1.1);
  } else if (ui->zoom_out) {
    scale_m(&ui->widget->file_data.vertexes, 0.9);
  }
  free(ui->widget->vertex_array);
  ui->widget->vertex_array = make_right_vert(ui->widget->file_data.vertexes);
}

void MainWindow::change_color() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->rib_color) {
    ui->widget->rib_color = QColorDialog::getColor(Qt::red, this, tr("colors"));
  } else if (button == ui->vert_color) {
    ui->widget->vert_color =
        QColorDialog::getColor(Qt::red, this, tr("colors"));
  } else if (button == ui->back_color) {
    ui->widget->back_color =
        QColorDialog::getColor(Qt::red, this, tr("colors"));
  }
}

void MainWindow::change_rib_size() {
  ui->widget->rib_size1 = ui->rib_size->value();
}

void MainWindow::change_lines_type() {
  if (ui->rib_type->currentText() == "Пунктирная") {
    ui->widget->line_type1 = 1;
  } else if (ui->rib_type->currentText() == "Сплошная") {
    ui->widget->line_type1 = 0;
  }
}

void MainWindow::change_tops_type() {
  if (ui->vert_type->currentText() == "Отсутствует") {
    ui->widget->display_tops1 = 0;
  } else if (ui->vert_type->currentText() == "Квадрат") {
    ui->widget->display_tops1 = 1;
  } else if (ui->vert_type->currentText() == "Круг") {
    ui->widget->display_tops1 = 2;
  }
}

void MainWindow::change_tops_size() {
  ui->widget->tops_size1 = ui->vert_size->value();
}

void MainWindow::set_start_settings() {
  ui->rib_size->setValue(ui->widget->rib_size1);
  ui->vert_type->setCurrentIndex(ui->widget->line_type1 == 0 ? 0 : 1);
  ui->vert_type->setCurrentIndex(ui->widget->display_tops1 == 0   ? 0
                                 : ui->widget->display_tops1 == 1 ? 1
                                                                  : 2);
  ui->vert_size->setValue(ui->widget->tops_size1);
  //    timer->stop();
}

void MainWindow::save_settings() {
  QSettings settings("settings.conf");
  settings.beginGroup("Configuretion");
  settings.setValue("shift_x", ui->mov_x_value->text());
  settings.setValue("shift_y", ui->mov_y_value->text());
  settings.setValue("shift_z", ui->mov_z_value->text());
  settings.setValue("rot_x", ui->rot_x_value->text());
  settings.setValue("rot_y", ui->rot_y_value->text());
  settings.setValue("rot_z", ui->rot_z_value->text());
  settings.setValue("rib_type", ui->rib_type->currentIndex());
  settings.setValue("ver_type", ui->vert_type->currentIndex());
  settings.setValue("file", ui->file_path_label->text());
  settings.setValue("rib_size", ui->rib_size->value());
  settings.setValue("vert_size", ui->vert_size->value());
  settings.setValue("img_format", ui->img_format->currentIndex());
  settings.setValue("rib_color", ui->widget->rib_color);
  settings.setValue("vert_color", ui->widget->vert_color);
  settings.setValue("back_color", ui->widget->back_color);
  settings.setValue("f_count", ui->f_count->text());
  settings.setValue("v_count", ui->v_count->text());
  settings.endGroup();
}

void MainWindow::take_settings() {
  QSettings settings("settings.conf");
  settings.beginGroup("Configuretion");
  ui->mov_x_value->setText(settings.value("shift_x", 0.0).toString());
  ui->mov_y_value->setText(settings.value("shift_y", 0.0).toString());
  ui->mov_z_value->setText(settings.value("shift_z", 0.0).toString());
  ui->rot_x_value->setText(settings.value("rot_x", 0.0).toString());
  ui->rot_y_value->setText(settings.value("rot_y", 0.0).toString());
  ui->rot_z_value->setText(settings.value("rot_z", 0.0).toString());
  ui->proect_type->setCurrentIndex(settings.value("pt_type", 0).toInt());
  ui->rib_type->setCurrentIndex(settings.value("rib_type", 0).toInt());
  ui->vert_type->setCurrentIndex(settings.value("ver_type", 0).toInt());
  ui->file_path_label->setText(settings.value("file").toString());
  ui->img_format->setCurrentIndex(settings.value("img_format", 0).toInt());
  ui->rib_size->setValue(settings.value("rib_size", 0).toInt());
  ui->vert_size->setValue(settings.value("vert_size", 0).toInt());
  ui->widget->rib_color = settings.value("rib_color").toString();
  ui->widget->vert_color = settings.value("vert_color").toString();
  ui->widget->back_color = settings.value("back_color").toString();
  ui->f_count->setText(settings.value("f_count", 0).toString());
  ui->v_count->setText(settings.value("v_count", 0).toString());
}

void MainWindow::make_gif() {
  QSize gif_size;
  gif_size.setWidth(640);
  gif_size.setHeight(480);
  QGifImage gif = QGifImage(gif_size);

  for (int i = 0; i < 100; ++i) {

    QScreen *screen = ui->widget->screen();
    gif.addFrame(screen
                     ->grabWindow(this->winId(), ui->widget->x(),
                                  ui->widget->y(), ui->widget->width(),
                                  ui->widget->height())
                     .toImage());
  }
  gif.save("../../../gif.gif");
}

void MainWindow::make_screen() {
  QScreen *screen = ui->widget->screen();
  QPixmap qpix =
      screen->grabWindow(this->winId(), ui->widget->x(), ui->widget->y(),
                         ui->widget->width(), ui->widget->height());

  qpix.save(QFileDialog::getSaveFileName() + ui->img_format->currentText());
}

void MainWindow::on_screen_but_clicked() { make_screen(); }

void MainWindow::on_gif_but_clicked() { ; }

void MainWindow::on_proect_type_currentTextChanged(const QString &arg1) {
  if (ui->proect_type->currentText() == "Параллельная") {
    ui->widget->projection_type = 0;
  } else if (ui->proect_type->currentText() == "Центральная") {
    ui->widget->projection_type = 1;
  }
}

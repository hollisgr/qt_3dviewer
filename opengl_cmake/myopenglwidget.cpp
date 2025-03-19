#include "myopenglwidget.h"

#include <fstream>
extern "C" {
#include "../common/s21_parser.h"
#include "../common/s21_transform.h"
}

myOpenGLWidget::myOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  data = {0, 0, NULL, NULL};
  proj_x = 2.0;
  proj_y = 2.0;
  proj_z = 5.0;
  load_settings();
}

myOpenGLWidget::~myOpenGLWidget() {
  clear_data(&data);
  save_settings();
}

void myOpenGLWidget::set_vp_color(double r, double g, double b, double a) {
  settings.vp_color_r = r;
  settings.vp_color_g = g;
  settings.vp_color_b = b;
  settings.vp_color_a = a;
}

void myOpenGLWidget::set_line_color(double r, double g, double b) {
  settings.l_color_r = r;
  settings.l_color_g = g;
  settings.l_color_b = b;
}

void myOpenGLWidget::set_vertex_color(double r, double g, double b) {
  settings.v_color_r = r;
  settings.v_color_g = g;
  settings.v_color_b = b;
}

void myOpenGLWidget::move_x(double value) { s21_move_x(&data, value); }

void myOpenGLWidget::move_y(double value) { s21_move_y(&data, value); }

void myOpenGLWidget::move_z(double value) { s21_move_z(&data, value); }

void myOpenGLWidget::rotate_x(double angle) { s21_rotate_x(&data, angle); }

void myOpenGLWidget::rotate_y(double angle) { s21_rotate_y(&data, angle); }

void myOpenGLWidget::rotate_z(double angle) { s21_rotate_z(&data, angle); }

void myOpenGLWidget::scale_model(double scale_value) {
  s21_scale(&data, scale_value);
}

void myOpenGLWidget::parse_obj(char *fileName) {
  clear_data(&data);
  ParsingFile(fileName, &data);
}

void myOpenGLWidget::set_line_type(int type) {
  if (type != 1 && type != 0)
    return;
  else
    settings.line_type = type;
}

void myOpenGLWidget::set_projection_type(int type) {
  if (type != 1 && type != 0)
    return;
  else
    settings.projection_type = type;
}

void myOpenGLWidget::set_vertex_type(int type) {
  if (type != 0 && type != 1 && type != 2)
    return;
  else
    settings.vertex_type = type;
}

void myOpenGLWidget::set_vertex_size(double value) {
  settings.vertex_size += value;
}

void myOpenGLWidget::set_line_size(double value) {
  settings.line_size += value;
}

int myOpenGLWidget::get_verteces_count() { return data.v_array_size / 3; }

int myOpenGLWidget::get_edges_count() { return data.i_array_size / 4; }

int myOpenGLWidget::get_line_type() { return settings.line_type; }

int myOpenGLWidget::get_projection_type() { return settings.projection_type; }

int myOpenGLWidget::get_vertex_type() { return settings.vertex_type; }

void myOpenGLWidget::save_settings() {
  std::ofstream out;
  out.open("ui.cfg");
  out << "line type: " << settings.line_type << std::endl;
  out << "line size: " << settings.line_size << std::endl;
  out << "projection type: " << settings.projection_type << std::endl;
  out << "vertex type: " << settings.vertex_type << std::endl;
  out << "vertex size: " << settings.vertex_size << std::endl;
  out << "viewport color: " << settings.vp_color_r << "/" << settings.vp_color_g
      << "/" << settings.vp_color_b << "/" << settings.vp_color_a << std::endl;
  out << "line color: " << settings.l_color_r << "/" << settings.l_color_g
      << "/" << settings.l_color_b << std::endl;
  out << "vertex color: " << settings.v_color_r << "/" << settings.v_color_g
      << "/" << settings.v_color_b << std::endl;
  out.close();
}

void myOpenGLWidget::load_settings() {
  std::ifstream in;
  char buffer[256];
  in.open("ui.cfg");
  in.getline(buffer, 256);
  sscanf(buffer, "line type: %d", &settings.line_type);
  in.getline(buffer, 256);
  sscanf(buffer, "line size: %lf", &settings.line_size);
  in.getline(buffer, 256);
  sscanf(buffer, "projection type: %d", &settings.projection_type);
  in.getline(buffer, 256);
  sscanf(buffer, "vertex type: %d", &settings.vertex_type);
  in.getline(buffer, 256);
  sscanf(buffer, "vertex size: %lf", &settings.vertex_size);
  in.getline(buffer, 256);
  sscanf(buffer, "viewport color: %lf/%lf/%lf/%lf", &settings.vp_color_r,
         &settings.vp_color_g, &settings.vp_color_b, &settings.vp_color_a);
  in.getline(buffer, 256);
  sscanf(buffer, "line color: %lf/%lf/%lf", &settings.l_color_r,
         &settings.l_color_g, &settings.l_color_b);
  in.getline(buffer, 256);
  sscanf(buffer, "vertex color: %lf/%lf/%lf", &settings.v_color_r,
         &settings.v_color_g, &settings.v_color_b);
  in.close();
}

void myOpenGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void myOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void myOpenGLWidget::paintGL() {
  glClearColor(settings.vp_color_r, settings.vp_color_g, settings.vp_color_b,
               settings.vp_color_a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (settings.projection_type) {
    glOrtho(-proj_x, proj_x, -proj_y, proj_y, -proj_z, proj_z);
  } else {
    perspective();
  }

  glVertexPointer(3, GL_DOUBLE, 0, data.vertex_array);

  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.line_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }

  glColor3d(settings.l_color_r, settings.l_color_g, settings.l_color_b);

  glDrawElements(GL_LINES, data.i_array_size, GL_UNSIGNED_INT,
                 data.index_array);

  if (settings.vertex_type != 0) {
    if (settings.vertex_type == 1) glEnable(GL_POINT_SMOOTH);
    glPointSize(settings.vertex_size);
    glLineWidth(settings.line_size);
    glColor3d(settings.v_color_r, settings.v_color_g, settings.v_color_b);
    glDrawArrays(GL_POINTS, 0, data.v_array_size / 3);
    if (settings.vertex_type == 1) glDisable(GL_POINT_SMOOTH);
  }

  if (settings.line_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void myOpenGLWidget::perspective() {
  double a_ratio = (proj_x * 100) / (proj_y * 100);
  double near = 1.0;
  double far = proj_z * 100;
  double fov_Y = proj_y * 10;
  double f_height = near * tan(fov_Y / 2.0);
  double f_width = f_height * a_ratio;
  glFrustum(-f_width, f_width, -f_height, f_height, near, far);
  glTranslated(0, 0, -f_height * 5);
}

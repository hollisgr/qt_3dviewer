#include "myopenglwidget.hpp"

#include <locale.h>

#include <fstream>

myOpenGLWidget::myOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  setlocale(LC_ALL, "");
  this->proj_x = 2.0;
  this->proj_y = 2.0;
  this->proj_z = 5.0;
  this->obj = nullptr;
  this->pars = new s21::s21_parser();
  this->load_settings();
}

myOpenGLWidget::~myOpenGLWidget() {
  this->save_settings();
  if (this->pars != nullptr) {
    delete this->pars;
    this->pars = nullptr;
  }
}

void myOpenGLWidget::set_vp_color(double r, double g, double b, double a) {
  this->settings.vp_color_r = r;
  this->settings.vp_color_g = g;
  this->settings.vp_color_b = b;
  this->settings.vp_color_a = a;
}

void myOpenGLWidget::set_line_color(double r, double g, double b) {
  this->settings.l_color_r = r;
  this->settings.l_color_g = g;
  this->settings.l_color_b = b;
}

void myOpenGLWidget::set_vertex_color(double r, double g, double b) {
  this->settings.v_color_r = r;
  this->settings.v_color_g = g;
  this->settings.v_color_b = b;
}

void myOpenGLWidget::move_x(double value) {
  if (obj != nullptr) obj->s21_move_x(value);
}

void myOpenGLWidget::move_y(double value) {
  if (obj != nullptr) obj->s21_move_y(value);
}

void myOpenGLWidget::move_z(double value) {
  if (obj != nullptr) obj->s21_move_z(value);
}

void myOpenGLWidget::rotate_x(double angle) {
  if (obj != nullptr) obj->s21_rotate_x(angle);
}

void myOpenGLWidget::rotate_y(double angle) {
  if (obj != nullptr) obj->s21_rotate_y(angle);
}

void myOpenGLWidget::rotate_z(double angle) {
  if (obj != nullptr) obj->s21_rotate_z(angle);
}

void myOpenGLWidget::scale_model(double scale_value) {
  if (obj != nullptr) obj->s21_scale(scale_value);
}

void myOpenGLWidget::parse_obj(char *fileName) {
  this->obj = this->pars->ParsingFile(fileName);
}

void myOpenGLWidget::set_line_type(int type) {
  if (type != 1 && type != 0)
    return;
  else
    this->settings.line_type = type;
}

void myOpenGLWidget::set_projection_type(int type) {
  if (type != 1 && type != 0)
    return;
  else
    this->settings.projection_type = type;
}

void myOpenGLWidget::set_vertex_type(int type) {
  if (type != 0 && type != 1 && type != 2)
    return;
  else
    this->settings.vertex_type = type;
}

void myOpenGLWidget::set_vertex_size(double value) {
  this->settings.vertex_size += value;
}

void myOpenGLWidget::set_line_size(double value) {
  this->settings.line_size += value;
}

int myOpenGLWidget::get_verteces_count() { return obj->get_v_arrey_size() / 3; }

int myOpenGLWidget::get_edges_count() { return obj->get_i_arrey_size() / 4; }

int myOpenGLWidget::get_line_type() { return this->settings.line_type; }

int myOpenGLWidget::get_projection_type() {
  return this->settings.projection_type;
}

int myOpenGLWidget::get_vertex_type() { return this->settings.vertex_type; }

void myOpenGLWidget::save_settings() {
  std::ofstream out;
  out.open("ui.cfg");
  out << "line_type: " << this->settings.line_type << std::endl;
  out << "line_size: " << this->settings.line_size << std::endl;
  out << "projection_type: " << this->settings.projection_type << std::endl;
  out << "vertex_type: " << this->settings.vertex_type << std::endl;
  out << "vertex_size: " << this->settings.vertex_size << std::endl;
  out << "viewport_color: " << this->settings.vp_color_r << " "
      << this->settings.vp_color_g << " " << this->settings.vp_color_b << " "
      << this->settings.vp_color_a << std::endl;
  out << "line_color: " << this->settings.l_color_r << " "
      << this->settings.l_color_g << " " << this->settings.l_color_b
      << std::endl;
  out << "vertex_color: " << this->settings.v_color_r << " "
      << this->settings.v_color_g << " " << this->settings.v_color_b
      << std::endl;
  out.close();
}

void myOpenGLWidget::load_settings() {
  std::ifstream in;
  in.open("ui.cfg");
  std::string str;
  while (std::getline(in, str)) {
    std::stringstream ss(str);
    std::string key;
    ss >> key;
    if (key == "line_type:")
      ss >> this->settings.line_type;
    else if (key == "line_size:")
      ss >> this->settings.line_size;
    else if (key == "projection_type:")
      ss >> this->settings.projection_type;
    else if (key == "vertex_type:")
      ss >> this->settings.vertex_type;
    else if (key == "vertex_size:")
      ss >> this->settings.vertex_size;
    else if (key == "viewport_color:")
      ss >> this->settings.vp_color_r >> this->settings.vp_color_g >>
          this->settings.vp_color_b >> this->settings.vp_color_a;
    else if (key == "line_color:")
      ss >> this->settings.l_color_r >> this->settings.l_color_g >>
          this->settings.l_color_b;
    else if (key == "vertex_color:")
      ss >> this->settings.v_color_r >> this->settings.v_color_g >>
          this->settings.v_color_b;
  }
  in.close();
}

void myOpenGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void myOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void myOpenGLWidget::paintGL() {
  if (obj != nullptr) {
    glClearColor(this->settings.vp_color_r, this->settings.vp_color_g,
                 this->settings.vp_color_b, this->settings.vp_color_a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (this->settings.projection_type) {
      glOrtho(-proj_x, proj_x, -proj_y, proj_y, -proj_z, proj_z);
    } else {
      perspective();
    }

    glVertexPointer(3, GL_DOUBLE, 0, obj->get_vertex_array()->data());
    glEnableClientState(GL_VERTEX_ARRAY);

    if (this->settings.vertex_type != 0) {
      if (this->settings.vertex_type == 1) glEnable(GL_POINT_SMOOTH);
      glPointSize(this->settings.vertex_size);
      glLineWidth(this->settings.line_size);
      glColor3d(this->settings.v_color_r, this->settings.v_color_g,
                this->settings.v_color_b);
      glDrawArrays(GL_POINTS, 0, obj->get_v_arrey_size() / 3);
      if (this->settings.vertex_type == 1) glDisable(GL_POINT_SMOOTH);
    }

    if (this->settings.line_type == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00FF);
    }

    glColor3d(this->settings.l_color_r, this->settings.l_color_g,
              this->settings.l_color_b);
    glDrawElements(GL_LINES, obj->get_i_arrey_size(), GL_UNSIGNED_INT,
                   obj->get_index_array()->data());

    if (this->settings.line_type == 1) {
      glDisable(GL_LINE_STIPPLE);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
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

#include "s21_transform.h"

void s21_rotate_x(obj_data_t *data, double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  int v_count = data->v_array_size;
  double *v_array = data->vertex_array;

  for (int i = 0; i < v_count; i += 3) {
    double temp_y = v_array[i + 1];
    double temp_z = v_array[i + 2];
    v_array[i + 1] = cos_a * temp_y - sin_a * temp_z;
    v_array[i + 2] = sin_a * temp_y + cos_a * temp_z;
  }
}

void s21_rotate_y(obj_data_t *data, double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  int v_count = data->v_array_size;
  double *v_array = data->vertex_array;

  for (int i = 0; i < v_count; i += 3) {
    double temp_x = v_array[i];
    double temp_z = v_array[i + 2];
    v_array[i] = cos_a * temp_x - sin_a * temp_z;
    v_array[i + 2] = sin_a * temp_x + cos_a * temp_z;
  }
}

void s21_rotate_z(obj_data_t *data, double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  int v_count = data->v_array_size;
  double *v_array = data->vertex_array;

  for (int i = 0; i < v_count; i += 3) {
    double temp_x = v_array[i];
    double temp_y = v_array[i + 1];
    v_array[i] = cos_a * temp_x - sin_a * temp_y;
    v_array[i + 1] = sin_a * temp_x + cos_a * temp_y;
  }
}

void s21_scale(obj_data_t *data, double scale_value) {
  if (scale_value != 0.0) {
    int v_count = data->v_array_size;
    double *v_array = data->vertex_array;

    for (int i = 0; i < v_count; i++) {
      v_array[i] *= scale_value;
    }
  }
}

void s21_move_x(obj_data_t *data, double value) {
  if (value != 0.0) {
    int v_count = data->v_array_size;
    double *v_array = data->vertex_array;

    for (int i = 0; i < v_count; i += 3) {
      v_array[i] += value;
    }
  }
}

void s21_move_y(obj_data_t *data, double value) {
  if (value != 0.0) {
    int v_count = data->v_array_size;
    double *v_array = data->vertex_array;

    for (int i = 0; i < v_count; i += 3) {
      v_array[i + 1] += value;
    }
  }
}

void s21_move_z(obj_data_t *data, double value) {
  if (value != 0.0) {
    int v_count = data->v_array_size;
    double *v_array = data->vertex_array;
    for (int i = 0; i < v_count; i += 3) {
      v_array[i + 2] += value;
    }
  }
}

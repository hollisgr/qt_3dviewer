#ifndef S21_TRANSFORM_H
#define S21_TRANSFORM_H

#include <math.h>
#include <stdlib.h>

#include "s21_struct.h"

#define S21_PI 3.14159265358979323846

void s21_rotate_x(obj_data_t *data, double angle);
void s21_rotate_y(obj_data_t *data, double angle);
void s21_rotate_z(obj_data_t *data, double angle);

void s21_scale(obj_data_t *data, double scale_value);

void s21_move_x(obj_data_t *data, double value);
void s21_move_y(obj_data_t *data, double value);
void s21_move_z(obj_data_t *data, double value);

#endif

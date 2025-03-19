#ifndef S21_STRUCT_H
#define S21_STRUCT_H

typedef struct {
  int v_array_size;
  int i_array_size;
  double *vertex_array;
  int *index_array;
} obj_data_t;

typedef struct {
  double min_x;
  double min_y;
  double min_z;
  double max_x;
  double max_y;
  double max_z;
} Min_Max_t;

#endif  // S21_STRUCT_H

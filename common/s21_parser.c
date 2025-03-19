#include "s21_parser.h"

#include <float.h>
#include <string.h>

#include "s21_struct.h"
#include "s21_transform.h"

int init_data(obj_data_t *data) {
  int error = OK;
  data->vertex_array = calloc(MAX_VERTICES, sizeof(double));
  data->index_array = calloc(MAX_VERTICES * 4, sizeof(int));
  data->i_array_size = 0;
  data->v_array_size = 0;
  return error;
}

void clear_data(obj_data_t *data) {
  free(data->vertex_array);
  free(data->index_array);
  data->vertex_array = NULL;
  data->index_array = NULL;
  data->v_array_size = 0;
  data->i_array_size = 0;
}

void ParseEdge(obj_data_t *data, char *str, int *it_f,
               int current_count_vertex) {
  char *var = strtok(str + 2, " ");
  unsigned index_f = 0;
  bool is_index_f = true;
  while (var) {
    long index = atoi(var);
    index -= 1;
    if (is_index_f && atoi(var)) {
      index_f = index;
      data->index_array[*it_f] = index;
      *it_f += 1;
      is_index_f = false;
    } else if (atoi(var)) {
      data->index_array[*it_f] = index;
      *it_f += 1;
      data->index_array[*it_f] = index;
      *it_f += 1;
    }
    var = strtok(NULL, " ");
  }
  data->index_array[*it_f] = index_f;
  *it_f += 1;
  current_count_vertex++;
}

int ParseVertex(obj_data_t *data, char *str, int *it_v,
                int *current_count_vertex, Min_Max_t *lim) {
  int error = OK;
  double x = 0, y = 0, z = 0;
  if (sscanf(str, "v %lf %lf %lf", &x, &y, &z) == 3) {
    data->vertex_array[*it_v] = x;
    *it_v += 1;
    data->vertex_array[*it_v] = y;
    *it_v += 1;
    data->vertex_array[*it_v] = z;
    *it_v += 1;
    *current_count_vertex += 1;

    lim->min_x = fmin(lim->min_x, x);
    lim->min_y = fmin(lim->min_y, y);
    lim->min_z = fmin(lim->min_z, z);

    lim->max_x = fmax(lim->max_x, x);
    lim->max_y = fmax(lim->max_y, y);
    lim->max_z = fmax(lim->max_z, z);
  } else
    error = INCORRECTDATA;
  return error;
}

int ParseData(FILE *file, obj_data_t *data) {
  int error = init_data(data);
  int buffer_size = 255, it_v = 0, it_f = 0, current_count_vertex = 0;
  Min_Max_t lim = {DBL_MAX, DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX, -DBL_MAX};
  if (error == OK) {
    char *str = (char *)malloc(buffer_size * sizeof(char));
    while (fgets(str, buffer_size, file) != NULL) {
      if (strncmp(str, "v ", 2) == 0) {
        error = ParseVertex(data, str, &it_v, &current_count_vertex, &lim);
      } else if (strncmp(str, "f ", 2) == 0) {
        ParseEdge(data, str, &it_f, current_count_vertex);
      }
    }
    free(str);
  }
  s21_move_x(data, -((lim.min_x + lim.max_x) / 2));
  s21_move_y(data, -((lim.min_y + lim.max_y) / 2));
  s21_move_z(data, -((lim.min_z + lim.max_z) / 2));
  data->v_array_size = it_v;
  data->i_array_size = it_f;
  return error;
}

int ParsingFile(char *filename, obj_data_t *data) {
  int error = OK;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    error = INCORRECTFILE;
  } else {
    error = ParseData(file, data);
    fclose(file);
    if (error == OK) {
      data->vertex_array = (double *)realloc(
          data->vertex_array, data->v_array_size * sizeof(double));
      data->index_array =
          (int *)realloc(data->index_array, data->i_array_size * sizeof(int));
    }
  }
  return error;
}

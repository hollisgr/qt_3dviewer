#ifndef S21_PARSER_H
#define S21_PARSER_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_struct.h"

#define MAX_VERTICES 1000000

enum { OK, INCORRECTFILE, INCORRECTDATA, MEMORYERROR };

int init_data(obj_data_t *data);
void clear_data(obj_data_t *data);
void ParseEdge(obj_data_t *data, char *str, int *it_f,
               int current_count_vertex);
int ParseVertex(obj_data_t *data, char *str, int *it_v,
                int *current_count_vertex, Min_Max_t *lim);
int ParseData(FILE *file, obj_data_t *data);
int ParsingFile(char *filename, obj_data_t *data);

#endif  // S21_PARSER

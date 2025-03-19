#include "test_main.h"
// rot +x
START_TEST(test_transform_1) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-1.000000, -0.366025, -1.366025, 1.000000,  -0.366025,
                    -1.366025, 1.000000,  1.366025,  -0.366025, -1.000000,
                    1.366025,  -0.366025, -1.000000, -1.366025, 0.366025,
                    1.000000,  -1.366025, 0.366025,  1.000000,  0.366025,
                    1.366025,  -1.000000, 0.366025,  1.366025};
  ParsingFile(filename, &data);
  s21_rotate_x(&data, 30);
  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);
  clear_data(&data);
}
END_TEST

// rot +y
START_TEST(test_transform_2) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-0.366025, -1.000000, -1.366025, 1.366025,  -1.000000,
                    -0.366025, 1.366025,  1.000000,  -0.366025, -0.366025,
                    1.000000,  -1.366025, -1.366025, -1.000000, 0.366025,
                    0.366025,  -1.000000, 1.366025,  0.366025,  1.000000,
                    1.366025,  -1.366025, 1.000000,  0.366025};
  ParsingFile(filename, &data);
  s21_rotate_y(&data, 30);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
}
END_TEST

// rot +z
START_TEST(test_transform_3) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-0.366025, -1.366025, -1.000000, 1.366025,  -0.366025,
                    -1.000000, 0.366025,  1.366025,  -1.000000, -1.366025,
                    0.366025,  -1.000000, -0.366025, -1.366025, 1.000000,
                    1.366025,  -0.366025, 1.000000,  0.366025,  1.366025,
                    1.000000,  -1.366025, 0.366025,  1.000000};
  int return_value = ParsingFile(filename, &data);
  s21_rotate_z(&data, 30);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// move +x
START_TEST(test_transform_4) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-0.900000, -1.000000, -1.000000, 1.100000,  -1.000000,
                    -1.000000, 1.100000,  1.000000,  -1.000000, -0.900000,
                    1.000000,  -1.000000, -0.900000, -1.000000, 1.000000,
                    1.100000,  -1.000000, 1.000000,  1.100000,  1.000000,
                    1.000000,  -0.900000, 1.000000,  1.000000};
  int return_value = ParsingFile(filename, &data);
  s21_move_x(&data, 0.1);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// move +y
START_TEST(test_transform_5) {
  obj_data_t data;
  double array[] = {-1.000000, -0.900000, -1.000000, 1.000000,  -0.900000,
                    -1.000000, 1.000000,  1.100000,  -1.000000, -1.000000,
                    1.100000,  -1.000000, -1.000000, -0.900000, 1.000000,
                    1.000000,  -0.900000, 1.000000,  1.000000,  1.100000,
                    1.000000,  -1.000000, 1.100000,  1.000000};
  char filename[] = "test_files/cube_simple.obj";
  int return_value = ParsingFile(filename, &data);
  s21_move_y(&data, 0.1);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// move +z
START_TEST(test_transform_6) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-1.000000, -1.000000, -0.900000, 1.000000,  -1.000000,
                    -0.900000, 1.000000,  1.000000,  -0.900000, -1.000000,
                    1.000000,  -0.900000, -1.000000, -1.000000, 1.100000,
                    1.000000,  -1.000000, 1.100000,  1.000000,  1.000000,
                    1.100000,  -1.000000, 1.000000,  1.100000};
  int return_value = ParsingFile(filename, &data);
  s21_move_z(&data, 0.1);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// scale ++
START_TEST(test_transform_7) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {-0.100000, -0.100000, -0.100000, 0.100000,  -0.100000,
                    -0.100000, 0.100000,  0.100000,  -0.100000, -0.100000,
                    0.100000,  -0.100000, -0.100000, -0.100000, 0.100000,
                    0.100000,  -0.100000, 0.100000,  0.100000,  0.100000,
                    0.100000,  -0.100000, 0.100000,  0.100000};
  int return_value = ParsingFile(filename, &data);
  s21_scale(&data, 0.1);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// scale --
START_TEST(test_transform_8) {
  obj_data_t data;
  char filename[] = "test_files/cube_simple.obj";
  double array[] = {0.100000,  0.100000,  0.100000,  -0.100000, 0.100000,
                    0.100000,  -0.100000, -0.100000, 0.100000,  0.100000,
                    -0.100000, 0.100000,  0.100000,  0.100000,  -0.100000,
                    -0.100000, 0.100000,  -0.100000, -0.100000, -0.100000,
                    -0.100000, 0.100000,  -0.100000, -0.100000};
  int return_value = ParsingFile(filename, &data);
  s21_scale(&data, -0.1);

  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);

  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

Suite *test_transform(void) {
  Suite *s = suite_create("s21_transform");
  TCase *tc = tcase_create("transform_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_transform_1);
  tcase_add_test(tc, test_transform_2);
  tcase_add_test(tc, test_transform_3);
  tcase_add_test(tc, test_transform_4);
  tcase_add_test(tc, test_transform_5);
  tcase_add_test(tc, test_transform_6);
  tcase_add_test(tc, test_transform_7);
  tcase_add_test(tc, test_transform_8);

  return s;
}

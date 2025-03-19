#include "test_main.h"

START_TEST(test_parser_1) {
  obj_data_t data;
  char filename[] = "primitives/Cube.obj";
  int return_value = ParsingFile(filename, &data);
  clear_data(&data);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(test_parser_2) {
  obj_data_t data;
  char filename[] = "Cube.obj";
  int return_value = ParsingFile(filename, &data);
  ck_assert_int_eq(return_value, INCORRECTFILE);
}
END_TEST

START_TEST(test_parser_3) {
  obj_data_t data;
  char filename[] = "test_files/Cube_bad.obj";
  int return_value = ParsingFile(filename, &data);
  clear_data(&data);
  ck_assert_int_eq(return_value, INCORRECTDATA);
}
END_TEST

START_TEST(test_parser_4) {
  obj_data_t data;
  double array[] = {0.366025,  1.549038,  -0.683013, 0.366025, -0.183013,
                    -1.683013, 1.366025,  0.683013,  0.816987, 1.366025,
                    -1.049038, -0.183013, -1.366025, 1.049038, 0.183013,
                    -1.366025, -0.683013, -0.816987, 0.366025, 0.183013,
                    1.683013,  -0.366025, -1.549038, 0.683013};
  char filename[] = "primitives/Cube.obj";
  ParsingFile(filename, &data);
  for (int i = 0; i < data.v_array_size; i++)
    ck_assert_int_eq(data.vertex_array[i], array[i]);
  clear_data(&data);
}
END_TEST

Suite *test_parser(void) {
  Suite *s = suite_create("s21_parser");
  TCase *tc = tcase_create("parser_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_parser_1);
  tcase_add_test(tc, test_parser_2);
  tcase_add_test(tc, test_parser_3);
  tcase_add_test(tc, test_parser_4);

  return s;
}

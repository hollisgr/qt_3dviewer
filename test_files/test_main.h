#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../common/s21_parser.h"
#include "../common/s21_struct.h"
#include "../common/s21_transform.h"

Suite *test_parser(void);
Suite *test_transform(void);

#endif  // SRC_TESTS_MAIN_H

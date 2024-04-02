#include "s21_convertor_test.h"

START_TEST(s21_from_int_to_decimal_test_1) {
  int a = 334567543;
  s21_decimal result = {{}};
  s21_decimal true_result = {{334567543, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  int a = -334567543;
  s21_decimal result = {{}};
  s21_decimal true_result = {{334567543, 0, 0, 1 << 31}};
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  int a = 2147483647;
  s21_decimal result = {{}};
  s21_decimal true_result = {{}};
  for (int i = 30; i >= 0; i--) {
    set_bit_mantis(&true_result, i, 1);
  }
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  int a = -2147483648;
  s21_decimal result = {{}};
  s21_decimal true_result = {{}};
  for (int i = 31; i >= 31; i--) {
    set_bit_mantis(&true_result, i, 1);
  }
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
  int a = 0;
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_6) {
  int a = 100;
  s21_decimal result = {{}};
  s21_decimal true_result = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_from_int_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

////////////////////////////////////////////////////////////

START_TEST(s21_from_float_to_decimal_test_7) {
  float a = 100.687;
  s21_decimal result = {{}};
  s21_decimal true_result = {{100687, 0, 0, 3 << 16}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_8) {
  float a = 25e-23;
  s21_decimal result = {{}};
  s21_decimal true_result = {{25, 0, 0, 23 << 16}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_9) {
  float a = 1e-28;
  s21_decimal result = {{}};
  s21_decimal true_result = {{1, 0, 0, 28 << 16}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_10) {
  float a = 79e-27;
  s21_decimal result = {{}};
  s21_decimal true_result = {{79, 0, 0, 27 << 16}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_11) {
  float a = -792281e-21;
  s21_decimal result = {{}};
  s21_decimal true_result = {{792281, 0, 0, 21 << 16}};
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_12) {
  float a = 7.9e6;
  s21_decimal result = {{}};
  s21_decimal true_result = {{7900000, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 0);
  ck_assert_int_eq(s21_is_equal(true_result, result), 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_13) {
  float a = 7.9e36;
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_from_float_to_decimal(a, &result), 1);
}
END_TEST

////////////////////////////////////////////////////////////

START_TEST(s21_from_decimal_to_int_test_14) {
  int a = 0;
  s21_decimal value = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_15) {
  int a = 0;
  s21_decimal value = {{}};
  for (int i = 30; i >= 0; i--) {
    set_bit_mantis(&value, i, 1);
  }
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 0);
  ck_assert_int_eq(a, 2147483647);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_16) {
  int a = 0;
  s21_decimal value = {{}};
  for (int i = 31; i >= 31; i--) {
    set_bit_mantis(&value, i, 1);
  }
  set_sign(&value, 1);
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 0);
  ck_assert_int_eq(a, -2147483648);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_17) {
  int a = 0;
  s21_decimal value = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_18) {
  int a = 0;
  s21_decimal value = {{0, 2, 0, 1 << 31}};
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_19) {
  int a = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(value, &a), 0);
  ck_assert_int_eq(a, 0);
}
END_TEST

////////////////////////////////////////////////////////////

START_TEST(s21_from_decimal_to_float_test_20) {
  float a = 0.0;
  s21_decimal value = {{0, 0, 0, 3 << 16}};
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq(a, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_21) {
  float a = 0.0;
  s21_decimal value = {{1, 0, 0, 28 << 16}};
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq(a, 1e-28);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_22) {
  float a = 0.0;
  s21_decimal value = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value, i, 1);
  }
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq_tol(a, 79228162514264337593543950335.00, 7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_23) {
  float a = 0.0;
  s21_decimal value = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value, i, 1);
  }
  set_sign(&value, 1);
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq_tol(a, -79228162514264337593543950335.00, 7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_24) {
  float a = 0.0;
  s21_decimal value = {{0, 0, 0, 28 << 16}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value, i, 1);
  }
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq_tol(a, 7.9228162514264337593543950335, 7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_25) {
  float a = 0.0;
  s21_decimal value = {{5646, 0, 0, 8 << 16}};
  ck_assert_int_eq(s21_from_decimal_to_float(value, &a), 0);
  ck_assert_float_eq_tol(a, 5646e-8, 7);
}
END_TEST

Suite* s21_convertor_suite_create(void) {
  Suite* suite = suite_create("s21_convertor_suite");
  TCase* tcase_core = tcase_create("s21_convertor_tcase");
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_1);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_2);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_3);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_4);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_5);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_6);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_7);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_8);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_9);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_10);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_11);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_12);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_13);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_14);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_15);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_16);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_17);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_18);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_19);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_20);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_21);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_22);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_23);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_24);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_25);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
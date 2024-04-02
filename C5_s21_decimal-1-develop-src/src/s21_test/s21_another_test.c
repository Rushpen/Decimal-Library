#include "s21_another_test.h"

START_TEST(s21_truncate_test_1) {
  s21_decimal value_1 = {{}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{7, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_exp(&value_1, 28);
  ck_assert_int_eq(s21_truncate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal value_1 = {{8917, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{891, 0, 0, 0}};
  ck_assert_int_eq(s21_truncate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal value_1 = {{8917, 0, 0, 5 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};
  set_sign(&value_1, 1);
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_truncate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_negate_test_4) {
  s21_decimal value_1 = {{8917, 0, 0, 5 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{8917, 0, 0, 5 << 16}};
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_negate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_negate_test_5) {
  s21_decimal value_1 = {{1, 0, 3, 5 << 16}};
  set_sign(&value_1, 1);
  s21_decimal result = {{}};
  s21_decimal true_result = {{1, 0, 3, 5 << 16}};

  ck_assert_int_eq(s21_negate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_negate_test_6) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_negate(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_7) {
  s21_decimal value_1 = {{}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{7, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_exp(&value_1, 28);
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_8) {
  s21_decimal value_1 = {{8917, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  set_sign(&value_1, 1);
  s21_decimal true_result = {{892, 0, 0, 0}};
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_9) {
  s21_decimal value_1 = {{8917, 0, 0, 5 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{1, 0, 0, 0}};
  set_sign(&value_1, 1);
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_10) {
  s21_decimal value_1 = {{}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{8, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_exp(&value_1, 28);
  set_sign(&value_1, 1);
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_11) {
  s21_decimal value_1 = {{8917, 0, 0, 2 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{89, 0, 0, 0}};
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_floor_test_12) {
  s21_decimal value_1 = {{0, 0, 1, 19 << 16}};
  set_sign(&value_1, 1);
  s21_decimal result = {{}};
  s21_decimal true_result = {{2, 0, 0, 0}};
  set_sign(&true_result, 1);
  ck_assert_int_eq(s21_floor(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_13) {
  s21_decimal value_1 = {{}};
  s21_decimal result = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_exp(&value_1, 28);
  s21_decimal true_result = {{8, 0, 0, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_14) {
  s21_decimal value_1 = {{8917, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{892, 0, 0, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_15) {
  s21_decimal value_1 = {{8917, 0, 0, 5 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_16) {
  s21_decimal value_1 = {{}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{8, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_exp(&value_1, 28);
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_17) {
  s21_decimal value_1 = {{8917, 0, 0, 2 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{89, 0, 0, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_18) {
  s21_decimal value_1 = {{0, 0, 1, 19 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{2, 0, 0, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_round_test_19) {
  s21_decimal value_1 = {{237, 0, 123456, 0}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{237, 0, 123456, 0}};
  ck_assert_int_eq(s21_round(value_1, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

Suite* s21_another_suite_create(void) {
  Suite* suite = suite_create("s21_another_suite");
  TCase* tcase_core = tcase_create("s21_another_tcase");
  tcase_add_test(tcase_core, s21_truncate_test_1);
  tcase_add_test(tcase_core, s21_truncate_test_2);
  tcase_add_test(tcase_core, s21_truncate_test_3);
  tcase_add_test(tcase_core, s21_negate_test_4);
  tcase_add_test(tcase_core, s21_negate_test_5);
  tcase_add_test(tcase_core, s21_negate_test_6);
  tcase_add_test(tcase_core, s21_floor_test_7);
  tcase_add_test(tcase_core, s21_floor_test_8);
  tcase_add_test(tcase_core, s21_floor_test_9);
  tcase_add_test(tcase_core, s21_floor_test_10);
  tcase_add_test(tcase_core, s21_floor_test_11);
  tcase_add_test(tcase_core, s21_floor_test_12);
  tcase_add_test(tcase_core, s21_round_test_13);
  tcase_add_test(tcase_core, s21_round_test_14);
  tcase_add_test(tcase_core, s21_round_test_15);
  tcase_add_test(tcase_core, s21_round_test_16);
  tcase_add_test(tcase_core, s21_round_test_17);
  tcase_add_test(tcase_core, s21_round_test_18);
  tcase_add_test(tcase_core, s21_round_test_19);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

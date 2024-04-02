#include "s21_comparison_test.h"

START_TEST(s21_is_equal_test_1) {
  s21_decimal value_1 = {{1, 0, 0, 1 << 16}};
  s21_decimal value_2 = {{10, 0, 0, 2 << 16}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_equal_test_2) {
  s21_decimal value_1 = {{9, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{10, 0, 0, 3 << 16}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_3) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_equal_test_4) {
  s21_decimal value_1 = {{10, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{9, 0, 0, 3 << 16}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_5) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_equal_test_6) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_7) {
  s21_decimal value_1 = {{1, 0, 0, 1 << 16}};
  s21_decimal value_2 = {{10, 0, 0, 2 << 16}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_8) {
  s21_decimal value_1 = {{1, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{0, 1, 0, 3 << 16}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_9) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_10) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_11) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_12) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_is_not_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_test_13) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_test_14) {
  s21_decimal value_1 = {{655, 12, 12, 10 << 16}};
  s21_decimal value_2 = {{1, 1, 1, 1 << 16}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_test_15) {
  s21_decimal value_1 = {{3, 4, 5, 6 << 16}};
  s21_decimal value_2 = {{8, 7, 6, 5 << 16}};
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_test_16) {
  s21_decimal value_1 = {{5, 6, 7, 2 << 16}};
  s21_decimal value_2 = {{6, 7, 8, 2 << 16}};
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_17) {
  s21_decimal value_1 = {{1, 1, 1, 1 << 16}};
  s21_decimal value_2 = {{1, 1, 1, 1 << 16}};
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_18) {
  s21_decimal value_1 = {{655, 344, 123, 3 << 16}};
  s21_decimal value_2 = {{654, 344, 123, 3 << 16}};
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_19) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{1000, 0, 0, 3 << 16}};
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_is_greater_test_20) {
  s21_decimal value_2 = {{}};
  s21_decimal value_1 = {{0, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_2, i, 1);
  }
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_greater_test_21) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_test_22) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_test_23) {
  s21_decimal value_1 = {{500000, 0, 0, 9 << 16}};
  s21_decimal value_2 = {{5, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_is_greater(value_2, value_1), 1);
}

START_TEST(s21_is_greater_or_equal_test_24) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_25) {
  s21_decimal value_1 = {{}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_26) {
  s21_decimal value_1 = {{500000, 0, 0, 6 << 16}};
  s21_decimal value_2 = {{5, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_is_greater_or_equal(value_2, value_1), 1);
}

START_TEST(s21_is_greater_test_27) {
  s21_decimal value_1 = {{500000, 0, 0, 6 << 16}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{500000, 0, 0, 6 << 16}};
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_2, value_1), 0);
}

START_TEST(s21_is_greater_test_28) {
  s21_decimal value_1 = {{500000, 0, 0, 6 << 16}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{500001, 0, 0, 6 << 16}};
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_2, value_1), 0);
}

START_TEST(s21_is_greater_test_29) {
  s21_decimal value_1 = {{500001, 0, 0, 6 << 16}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{500000, 0, 0, 6 << 16}};
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_2, value_1), 1);
}

START_TEST(s21_is_less_test_30) {
  s21_decimal value_1 = {{5, 6, 7, 2 << 16}};
  s21_decimal value_2 = {{6, 7, 8, 2 << 16}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_test_31) {
  s21_decimal value_1 = {{1230, 865, 5, 2 << 16}};
  s21_decimal value_2 = {{123, 235, 6, 2 << 16}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_test_32) {
  s21_decimal value_2 = {{1230, 865, 5, 2 << 16}};
  s21_decimal value_1 = {{123, 235, 6, 2 << 16}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_test_33) {
  s21_decimal value_1 = {{0, 123, 65, 0}};
  s21_decimal value_2 = {{0, 123, 6, 0}};
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

Suite* s21_comparison_suite_create(void) {
  Suite* suite = suite_create("s21_comparison_suite");
  TCase* tcase_core = tcase_create("s21_comparison_tcase");
  tcase_add_test(tcase_core, s21_is_equal_test_1);
  tcase_add_test(tcase_core, s21_is_equal_test_2);
  tcase_add_test(tcase_core, s21_is_equal_test_3);
  tcase_add_test(tcase_core, s21_is_equal_test_4);
  tcase_add_test(tcase_core, s21_is_equal_test_5);
  tcase_add_test(tcase_core, s21_is_equal_test_6);
  tcase_add_test(tcase_core, s21_is_not_equal_test_7);
  tcase_add_test(tcase_core, s21_is_not_equal_test_8);
  tcase_add_test(tcase_core, s21_is_not_equal_test_9);
  tcase_add_test(tcase_core, s21_is_not_equal_test_10);
  tcase_add_test(tcase_core, s21_is_not_equal_test_11);
  tcase_add_test(tcase_core, s21_is_not_equal_test_12);
  tcase_add_test(tcase_core, s21_is_less_test_13);
  tcase_add_test(tcase_core, s21_is_less_test_14);
  tcase_add_test(tcase_core, s21_is_less_test_15);
  tcase_add_test(tcase_core, s21_is_less_test_16);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_17);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_18);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_19);
  tcase_add_test(tcase_core, s21_is_greater_test_20);
  tcase_add_test(tcase_core, s21_is_greater_test_21);
  tcase_add_test(tcase_core, s21_is_greater_test_22);
  tcase_add_test(tcase_core, s21_is_greater_test_23);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_24);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_25);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_26);
  tcase_add_test(tcase_core, s21_is_greater_test_27);
  tcase_add_test(tcase_core, s21_is_greater_test_28);
  tcase_add_test(tcase_core, s21_is_greater_test_29);
  tcase_add_test(tcase_core, s21_is_less_test_30);
  tcase_add_test(tcase_core, s21_is_less_test_31);
  tcase_add_test(tcase_core, s21_is_less_test_32);
  tcase_add_test(tcase_core, s21_is_less_test_33);
  suite_add_tcase(suite, tcase_core);

  return suite;
}
#include "s21_arithmetic_test.h"

START_TEST(s21_add_test_1) {
  s21_decimal value_1 = {{1, 2, 3, 1 << 16}};
  s21_decimal value_2 = {{1, 2, 0, 1 << 15}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal value_1 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 1);
}
END_TEST

START_TEST(s21_add_test_3) {
  s21_decimal value_1 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 2);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal value_1 = {{0, 0, 0, 27 << 16}};
  s21_decimal value_2 = {{0, 0, 0, 27 << 16}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  s21_decimal result = {{}};
  s21_decimal prec_result = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, prec_result), 1);
}
END_TEST

//////////////////////////////////////////////////////////////

START_TEST(s21_sub_test_7) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  s21_decimal result = {{}};
  s21_decimal prec_result = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, prec_result), 1);
}
END_TEST

START_TEST(s21_sub_test_8) {
  s21_decimal value_1 = {{0, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 2);
}
END_TEST

START_TEST(s21_sub_test_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&value_2, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 1);
}
END_TEST

START_TEST(s21_sub_test_10) {
  s21_decimal value_1 = {{1000000, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{100, 0, 0, 2 << 16}};
  s21_decimal result = {{}};
  s21_decimal prec_result = {{999, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, prec_result), 1);
}
END_TEST

START_TEST(s21_sub_test_11) {
  s21_decimal value_1 = {{1000000, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{100, 0, 0, 2 << 16}};
  s21_decimal result = {{}};
  s21_decimal prec_result = {{999, 0, 0, 0}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, prec_result), 1);
}
END_TEST

START_TEST(s21_sub_test_12) {
  s21_decimal value_1 = {{1000000, 0, 0, 3 << 16}};
  s21_decimal value_2 = {{100, 0, 0, 1 << 16}};
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  s21_decimal result = {{}};
  s21_decimal prec_result = {{990, 0, 0, 1 << 31}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, prec_result), 1);
}
END_TEST

START_TEST(s21_sub_test_13) {
  s21_decimal value_1 = {{0, 0, 0, 29 << 16}};
  s21_decimal value_2 = {{0, 0, 0, 1 << 31}};
  for (int i = 96; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 2);
}
END_TEST

START_TEST(s21_sub_test_14) {
  s21_decimal value_1 = {{0, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
}
END_TEST

//////////////////////////////////////////////////////////////

START_TEST(s21_mul_test_15) {
  s21_decimal value_1 = {{0, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  s21_decimal true_result = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&true_result, i, 1);
  }
  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_mul_test_16) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  s21_decimal true_result = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&true_result, i, 1);
  }
  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_mul_test_17) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_mul_test_18) {
  s21_decimal value_1 = {{156321, 0, 0, 4 << 16}};
  s21_decimal value_2 = {{100, 0, 0, 3 << 16}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{15632100, 0, 0, 7 << 16}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_mul_test_19) {
  s21_decimal value_1 = {{0, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{1, 0, 0, 10 << 16}};
  s21_decimal true_result = {{0, 0, 0, 1 << 31}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&true_result, i, 1);
  }
  set_exp(&true_result, 10);
  s21_decimal result = {{}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_mul_test_20) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 28 << 16}};
  s21_decimal true_result = {{0, 0, 0, 28 << 16}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&true_result, i, 1);
  }
  s21_decimal result = {{}};

  ck_assert_int_eq(s21_mul(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

////////////

START_TEST(s21_sub_bank_test_21) {
  s21_decimal value_1 = {{}};
  s21_decimal true_result = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&true_result, i, 1);
  }
  set_bit_mantis(&true_result, 0, 0);
  s21_decimal value_2 = {{5, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_sub_dop_test_22) {
  s21_decimal value_1 = {{1, 2, 3, 0}};
  s21_decimal value_2 = {{2, 3, 4, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_sub_dop_test_23) {
  s21_decimal value_1 = {{}};
  s21_decimal true_result = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&true_result, i, 1);
  }
  set_bit_mantis(&true_result, 0, 0);
  s21_decimal value_2 = {{15, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_sub(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_add_dop_test_24) {
  s21_decimal value_1 = {{}};
  s21_decimal true_result = {{}};
  for (int i = 95; i >= 1; i--) {
    set_bit_mantis(&value_1, i, 1);
    set_bit_mantis(&true_result, i, 1);
  }
  s21_decimal value_2 = {{5, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

/////////////////////////////////////////////////////////////////
START_TEST(s21_div_test_25) {
  s21_decimal value_1 = {{100, 0, 0, 1 << 16}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 16}};
  s21_decimal true_result = {{100, 0, 0, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_div_test_26) {
  s21_decimal value_1 = {{100, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  s21_decimal true_result = {{100, 0, 0, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_div_test_27) {
  s21_decimal value_1 = {{100, 0, 0, 1 << 16}};
  s21_decimal value_2 = {{1, 0, 0, 1 << 31}};
  s21_decimal true_result = {{10, 0, 0, 1 << 31}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

START_TEST(s21_div_test_28) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 1 << 16}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_div_test_29) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
}
END_TEST

START_TEST(s21_div_test_30) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{}};
  s21_decimal true_result = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(value_1, value_2, &result), 3);
  ck_assert_int_eq(s21_is_equal(result, true_result), 1);
}
END_TEST

//////////////////////////////////////////////////////////////
START_TEST(s21_add_dop_test_31) {
  s21_decimal value_1 = {{}};
  for (int i = 95; i >= 0; i--) {
    set_bit_mantis(&value_1, i, 1);
  }
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 1);
}
END_TEST

START_TEST(s21_add_dop_test_32) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{50, 0, 0, 1 << 31}};
  s21_decimal result = {{}};
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 0);
}
END_TEST

///////////////////////////////////////////////////////////////

Suite* s21_arithmetic_suite_create(void) {
  Suite* suite = suite_create("s21_arithmetic_suite");
  TCase* tcase_core = tcase_create("s21_arithmetic_tcase");
  tcase_add_test(tcase_core, s21_add_test_1);
  tcase_add_test(tcase_core, s21_add_test_2);
  tcase_add_test(tcase_core, s21_add_test_3);
  tcase_add_test(tcase_core, s21_add_test_4);
  tcase_add_test(tcase_core, s21_add_test_5);
  tcase_add_test(tcase_core, s21_add_test_6);
  tcase_add_test(tcase_core, s21_sub_test_7);
  tcase_add_test(tcase_core, s21_sub_test_8);
  tcase_add_test(tcase_core, s21_sub_test_9);
  tcase_add_test(tcase_core, s21_sub_test_10);
  tcase_add_test(tcase_core, s21_sub_test_11);
  tcase_add_test(tcase_core, s21_sub_test_12);
  tcase_add_test(tcase_core, s21_sub_test_13);
  tcase_add_test(tcase_core, s21_sub_test_14);
  tcase_add_test(tcase_core, s21_mul_test_15);
  tcase_add_test(tcase_core, s21_mul_test_16);
  tcase_add_test(tcase_core, s21_mul_test_17);
  tcase_add_test(tcase_core, s21_mul_test_18);
  tcase_add_test(tcase_core, s21_mul_test_19);
  tcase_add_test(tcase_core, s21_mul_test_20);
  tcase_add_test(tcase_core, s21_sub_bank_test_21);
  tcase_add_test(tcase_core, s21_sub_dop_test_22);
  tcase_add_test(tcase_core, s21_sub_dop_test_23);
  tcase_add_test(tcase_core, s21_add_dop_test_24);
  tcase_add_test(tcase_core, s21_div_test_25);
  tcase_add_test(tcase_core, s21_div_test_26);
  tcase_add_test(tcase_core, s21_div_test_27);
  tcase_add_test(tcase_core, s21_div_test_28);
  tcase_add_test(tcase_core, s21_div_test_29);
  tcase_add_test(tcase_core, s21_div_test_30);
  tcase_add_test(tcase_core, s21_add_dop_test_31);
  tcase_add_test(tcase_core, s21_add_dop_test_32);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
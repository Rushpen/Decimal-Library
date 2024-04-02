#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int exponent = 0;
  reset_decimal(result);

  big_decimal big_result;
  reset_big_decimal(&big_result);

  int sign_1 = check_sign(value_1);
  int sign_2 = check_sign(value_2);

  if (sign_1 == 0 && sign_2 == 0) {
    error = mul_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 0);
    }
  } else if (sign_1 && sign_2) {
    error = mul_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 0);
    }
  } else if (sign_1 || sign_2) {
    error = mul_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 1);
    }
  }

  return error;
}

int mul_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result,
            int *exponent) {
  int error = 0;
  *exponent = check_exp(value_1) + check_exp(value_2);
  big_decimal big_1;
  big_decimal big_2;
  reset_big_decimal(&big_1);
  reset_big_decimal(&big_2);
  reset_big_decimal(big_result);

  mantis_to_big_mantis(value_1, &big_1);
  mantis_to_big_mantis(value_2, &big_2);

  mul_big_mantis(big_1, big_2, big_result);
  error = normalization_exp(big_result, exponent);

  return error;
}

int mul_big_mantis(big_decimal value_1, big_decimal value_2,
                   big_decimal *result) {
  reset_big_decimal(result);
  big_decimal buf;
  reset_big_decimal(&buf);
  int error = 0;
  int end = check_big_mantis(value_2);

  for (int i = 0; i <= end; i++) {
    int check_2 = check_bit_big_mantis(value_2, i);
    if (check_2 == 1) {
      add_big_mantis(value_1, buf, result);
      buf = *result;
    }
    error = shift_to_left_big(&value_1);
  }
  return error;
}
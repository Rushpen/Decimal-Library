#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int exponent = 0;
  reset_decimal(result);

  big_decimal big_result;
  reset_big_decimal(&big_result);

  int sign_1 = check_sign(value_1);
  int sign_2 = check_sign(value_2);
  if (check_mantis(value_2) == -1) {
    error = 3;
    reset_decimal(result);
  } else if (sign_1 == 0 && sign_2 == 0) {
    error = div_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 0);
    }
  } else if (sign_1 && sign_2) {
    error = div_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 0);
    }
  } else if (sign_1 || sign_2) {
    error = div_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 1);
    }
  }

  return error;
}

int div_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result,
            int *exponent) {
  int error = 0;
  *exponent = check_exp(value_1) - check_exp(value_2);
  big_decimal big_1;
  big_decimal big_2;
  big_decimal big_3;
  big_decimal remainder;
  big_decimal zero = {{0}};
  big_decimal isDec = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  reset_big_decimal(&big_1);
  reset_big_decimal(&big_2);
  reset_big_decimal(&big_3);
  reset_big_decimal(big_result);
  reset_big_decimal(&remainder);

  mantis_to_big_mantis(value_1, &big_1);
  mantis_to_big_mantis(value_2, &big_2);

  if ((*exponent) < 0) {
    for (; (*exponent) < 0; (*exponent)++) {
      mul_big_mantis(big_1, isDec, big_result);
      big_1 = *big_result;
    }
  }

  div_big_mantis(big_1, big_2, &remainder, big_result);
  int check_zero = is_equal_big_mantis(zero, remainder);
  if (!check_zero) {
    for (; (*exponent) < 28 && check_zero == 0; (*exponent)++) {
      mul_big_mantis(remainder, isDec, &big_1);
      remainder = big_1;
      mul_big_mantis(*big_result, isDec, &big_1);
      *big_result = big_1;
      div_big_mantis(remainder, big_2, &big_3, &big_1);
      remainder = big_3;
      add_big_mantis(*big_result, big_1, &big_3);
      *big_result = big_3;

      check_zero = is_equal_big_mantis(zero, remainder);
    }
  }

  error = normalization_exp(big_result, exponent);
  return error;
}

int div_big_mantis(big_decimal value_1, big_decimal value_2,
                   big_decimal *remainder, big_decimal *result) {
  reset_big_decimal(result);
  reset_big_decimal(remainder);

  big_decimal buf;
  reset_big_decimal(&buf);
  int error = 0;

  int n1 = check_big_mantis(value_1);
  int n2 = check_big_mantis(value_2);
  int n = abs(n1 - n2);

  *remainder = value_1;
  for (int i = 0; i < n; i++) {
    shift_to_right_big(&*remainder);
  }
  buf = *remainder;
  for (int i = n; i >= 0; i--) {
    shift_to_left_big(result);
    if (is_greater_or_equal_big_mantis(*remainder, value_2)) {
      sub_big_mantis(*remainder, value_2, &buf);
      set_bit_big_mantis(result, 0, 1);
    }

    if (i > 0) {
      shift_to_left_big(&buf);
      if (check_bit_big_mantis(value_1, (i - 1))) {
        set_bit_big_mantis(&buf, 0, 1);
      }
    }
    *remainder = buf;
  }
  return error;
}

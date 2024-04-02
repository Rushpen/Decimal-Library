#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int exponent = 0;
  reset_decimal(result);

  big_decimal big_result;
  reset_big_decimal(&big_result);

  int sign_1 = check_sign(value_1);
  int sign_2 = check_sign(value_2);

  if (sign_1 == 0 && sign_2 == 0) {
    error = add_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 0);
    }
  } else if (sign_1 && sign_2) {
    error = add_man(value_1, value_2, &big_result, &exponent);
    if (error == 0) {
      big_mantis_to_mantis(result, big_result, exponent, 1);
    } else {
      error = 2;
    }
  } else if (sign_1 || sign_2) {
    if (sign_1) {
      set_sign(&value_1, 0);
      error = s21_sub(value_2, value_1, result);
    } else {
      set_sign(&value_2, 0);
      error = s21_sub(value_1, value_2, result);
    }
  }

  return error;
}

int add_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result,
            int *exponent) {
  int error = 0;
  big_decimal big_1;
  big_decimal big_2;
  reset_big_decimal(&big_1);
  reset_big_decimal(&big_2);
  reset_big_decimal(big_result);
  int c = normalization(value_1, value_2, &big_1, &big_2, exponent);
  if (c == 0) {
    add_big_mantis(big_1, big_2, big_result);
    error = normalization_exp(big_result, exponent);
  }

  return error;
}

int add_big_mantis(big_decimal value_1, big_decimal value_2,
                   big_decimal *result) {
  reset_big_decimal(result);
  int in_mind = 0;
  int error = 0;
  for (int i = 0; i < 288; i++) {
    int check_1 = check_bit_big_mantis(value_1, i);
    int check_2 = check_bit_big_mantis(value_2, i);

    if ((check_1 == 1 && check_2 == 1) && in_mind == 0) {
      in_mind = 1;
    } else if ((check_1 == 1 && check_2 == 1) && in_mind == 1) {
      set_bit_big_mantis(result, i, 1);
      in_mind = 1;
    } else if ((check_1 == 1 || check_2 == 1) && in_mind == 0) {
      set_bit_big_mantis(result, i, 1);
    } else if ((check_1 == 1 || check_2 == 1) && in_mind == 1) {
      in_mind = 1;
    } else if ((check_1 == 0 && check_2 == 0) && in_mind == 1) {
      set_bit_big_mantis(result, i, 1);
      in_mind = 0;
    }
  }
  return error;
}

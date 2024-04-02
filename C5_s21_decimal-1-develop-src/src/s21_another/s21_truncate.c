#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  reset_decimal(result);
  int exp = check_exp(value);
  int sign = check_sign(value);
  s21_decimal exp_dec;
  reset_decimal(&exp_dec);
  big_decimal big_exp_dec;
  reset_big_decimal(&big_exp_dec);
  big_decimal dop_val;
  reset_big_decimal(&dop_val);
  big_decimal big_value;
  reset_big_decimal(&big_value);
  mantis_to_big_mantis(value, &big_value);

  s21_from_int_to_decimal(10, &exp_dec);
  mantis_to_big_mantis(exp_dec, &big_exp_dec);

  big_decimal remainder;
  reset_big_decimal(&remainder);

  for (int i = 0; i < exp; i++) {
    dop_val = big_value;
    div_big_mantis(dop_val, big_exp_dec, &remainder, &big_value);
  }

  big_mantis_to_mantis(result, big_value, 0, sign);
  return error;
}

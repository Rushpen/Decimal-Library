#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int sign = check_sign(value);
  reset_decimal(result);

  big_decimal big_result;
  reset_big_decimal(&big_result);

  big_decimal prec_big_res;
  reset_big_decimal(&prec_big_res);

  error = s21_truncate(value, result);

  if (sign == 1 && s21_is_not_equal(value, *result)) {
    mantis_to_big_mantis(*result, &big_result);
    big_decimal one;
    reset_big_decimal(&one);
    set_bit_big_mantis(&one, 0, 1);
    error = add_big_mantis(big_result, one, &prec_big_res);
    reset_decimal(result);
    big_mantis_to_mantis(result, prec_big_res, 0, sign);
  }

  return error;
}
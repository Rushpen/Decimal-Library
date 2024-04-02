#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int sign = check_sign(value);
  int exp = check_exp(value);
  if (exp > 0) {
    s21_decimal prec_res;
    reset_decimal(&prec_res);

    s21_decimal half = {{5, 0, 0, 1 << 16}};
    s21_add(value, half, &prec_res);
    reset_decimal(result);
    error = s21_truncate(prec_res, result);
  } else {
    *result = value;
    set_sign(result, sign);
  }

  return error;
}
#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  big_decimal prec_res;
  reset_big_decimal(&prec_res);
  int error = 0;
  int exp = 0;
  int sign = 0;
  float dop_float = 0;
  if (src < 0.0) {
    src = fabs(src);
    sign = 1;
  }

  if (src < S21_FLOAT_MIN || src > S21_FLOAT_MAX) {
    error = 1;
  } else {
    dop_float = src;
    while ((long)dop_float != dop_float && exp < 28) {
      dop_float *= 10;
      exp++;
    }
  }
  prec_res.bits[0] = round(dop_float);
  big_mantis_to_mantis(dst, prec_res, exp, sign);
  return error;
}
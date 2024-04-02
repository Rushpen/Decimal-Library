#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int sign = check_sign(src);
  long int prec_res = 0;
  *dst = 0;

  s21_decimal dst_dec;
  reset_decimal(&dst_dec);
  error = s21_truncate(src, &dst_dec);

  for (int i = check_mantis(dst_dec); i >= 0; i--) {
    prec_res += check_bit_mantis(dst_dec, i) * pow(2, i);
  }
  if (sign == 1) prec_res *= -sign;
  if (prec_res > S21_INT_MAX || prec_res < S21_INT_MIN) {
    error = 1;
  } else {
    *dst = (int)prec_res;
  }

  return error;
}
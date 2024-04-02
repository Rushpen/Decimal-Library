#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  int sign = check_sign(src);
  int exponent = check_exp(src);
  *dst = 0;
  long tempValue;

  for (int i = 2; i >= 0; i--) {
    tempValue = (long)src.bits[i];
    if (tempValue < 0) tempValue += 4294967296;
    *dst += tempValue;
    if (i != 0) *dst *= 4294967296;
  }
  for (int i = 0; i < exponent; i++) {
    *dst /= 10;
  }
  if (sign == 1) {
    *dst *= -1;
  }

  return error;
}
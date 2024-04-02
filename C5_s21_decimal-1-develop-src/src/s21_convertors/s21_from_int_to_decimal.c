#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset_decimal(dst);
  int sign = (src >> 31) * -1;
  src = abs(src);
  dst->bits[0] = src;
  set_sign(dst, sign);

  return 0;
}

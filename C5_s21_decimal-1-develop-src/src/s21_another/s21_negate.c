#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  reset_decimal(result);
  *result = value;
  swap_sign(result);
  return 0;
}
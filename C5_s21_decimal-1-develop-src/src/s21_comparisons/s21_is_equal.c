#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int z;
  big_decimal big_1;
  big_decimal big_2;
  reset_big_decimal(&big_1);
  reset_big_decimal(&big_2);

  if (check_sign(value_1) != check_sign(value_2)) {
    if (check_mantis(value_1) == -1 && check_mantis(value_2) == -1)
      result = 1;
    else
      result = 0;
  } else {
    if (check_exp(value_1) == check_exp(value_2)) {
      result = is_equal_mantis(value_1, value_2);
    } else {
      normalization(value_1, value_2, &big_1, &big_2, &z);
      result = is_equal_big_mantis(big_1, big_2);
    }
  }
  return result;
}
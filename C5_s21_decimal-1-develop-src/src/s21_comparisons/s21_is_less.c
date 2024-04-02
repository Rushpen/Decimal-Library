#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int z;
  big_decimal big_1;
  big_decimal big_2;
  reset_big_decimal(&big_1);
  reset_big_decimal(&big_2);

  if (check_sign(value_1) > check_sign(value_2)) {
    result = 1;
  } else if (check_sign(value_1) == check_sign(value_2)) {
    if (check_exp(value_1) == check_exp(value_2)) {
      if (check_sign(value_1) == 0)
        result = is_less_mantis(value_1, value_2);
      else
        result = is_greater_mantis(value_1, value_2);
    } else {
      normalization(value_1, value_2, &big_1, &big_2, &z);
      if (check_sign(value_1) == 0)
        result = is_less_big_mantis(big_1, big_2);
      else
        result = is_greater_big_mantis(big_1, big_2);
    }
  }
  return result;
}
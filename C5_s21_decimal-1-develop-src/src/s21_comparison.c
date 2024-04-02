#include "s21_decimal.h"

int is_less_mantis(s21_decimal value_1, s21_decimal value_2) {
  int result = -1;
  int check_mantis_1 = check_mantis(value_1);
  int check_mantis_2 = check_mantis(value_2);

  if (check_mantis_1 < check_mantis_2) {
    result = 1;
  } else if (is_equal_mantis(value_1, value_2)) {
    result = 0;
  } else if (check_mantis_1 == check_mantis_2) {
    for (int i = check_mantis_1; i >= 0 && result == -1; i--) {
      if (check_bit_mantis(value_1, i) < check_bit_mantis(value_2, i)) {
        result = 1;
      } else if (check_bit_mantis(value_1, i) > check_bit_mantis(value_2, i)) {
        result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int is_greater_mantis(s21_decimal value_1, s21_decimal value_2) {
  int result = -1;
  int check_mantis_1 = check_mantis(value_1);
  int check_mantis_2 = check_mantis(value_2);

  if (check_mantis_1 > check_mantis_2) {
    result = 1;
  } else if (is_equal_mantis(value_1, value_2)) {
    result = 0;
  } else if (check_mantis_1 == check_mantis_2) {
    for (int i = check_mantis_1; i >= 0 && result == -1; i--) {
      if (check_bit_mantis(value_1, i) > check_bit_mantis(value_2, i)) {
        result = 1;
      } else if (check_bit_mantis(value_1, i) < check_bit_mantis(value_2, i)) {
        result = 0;
      }
    }
  }
  return result;
}

int is_equal_mantis(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  int check_mantis_1 = check_mantis(value_1);
  int check_mantis_2 = check_mantis(value_2);

  if (check_mantis_1 == check_mantis_2) {
    for (int i = check_mantis_1; i >= 0 && result == 1; i--) {
      if (check_bit_mantis(value_1, i) > check_bit_mantis(value_2, i)) {
        result = 0;
      } else if (check_bit_mantis(value_1, i) < check_bit_mantis(value_2, i)) {
        result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

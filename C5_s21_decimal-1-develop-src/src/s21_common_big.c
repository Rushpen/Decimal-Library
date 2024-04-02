#include "s21_decimal.h"

int check_bit_big_mantis(big_decimal bigdecimal, int check) {
  int result = -3;
  int c = 0;
  int d = check;
  int i = 0;
  for (; d >= 32; i++) {
    c = i * 32;
    d = check - c;
    c = 0;
  }
  c = check % 32;
  result = check_bit(bigdecimal.bits[i], check % 32);

  return result;
}

int swap_bit_big_mantis(big_decimal *bigdecimal, int check) {
  unsigned one = 0;
  int c = 0;
  int d = check;
  int i = 0;
  for (; d >= 32; i++) {
    c = i * 32;
    d = check - c;
    c = 0;
  }
  check = check % 32;
  one = 1 << check;
  bigdecimal->bits[i] = bigdecimal->bits[i] ^ one;

  return 0;
}

int set_bit_big_mantis(big_decimal *bigdecimal, int check, int set) {
  if (check_bit_big_mantis(*bigdecimal, check)) {
    if (set == 0) {
      swap_bit_big_mantis(bigdecimal, check);
    }
  } else {
    if (set == 1) {
      swap_bit_big_mantis(bigdecimal, check);
    }
  }
  return 0;
}

int mantis_to_big_mantis(s21_decimal decimal, big_decimal *bigdecimal) {
  for (int i = 0; i < 96; i++) {
    if (check_bit_mantis(decimal, i)) {
      set_bit_big_mantis(bigdecimal, i, 1);
    }
  }
  return 0;
}

int big_mantis_to_mantis(s21_decimal *decimal, big_decimal bigdecimal, int exp,
                         int sign) {
  for (int i = 0; i < 96; i++) {
    if (check_bit_big_mantis(bigdecimal, i)) {
      set_bit_mantis(decimal, i, 1);
    }
  }
  set_exp(decimal, exp);
  set_sign(decimal, sign);
  return 0;
}

int check_big_mantis(big_decimal decimal) {
  int result = -1;

  for (int i = 0; i < 288; i++) {
    if (check_bit_big_mantis(decimal, i)) {
      result = i;
    }
  }
  return result;
}

int shift_to_left_big(big_decimal *bigdecimal) {
  int end_bit = 0;
  int bit = 0;
  big_decimal result;
  reset_big_decimal(&result);
  for (int i = 0; i < 288; i++) {
    bit = check_bit_big_mantis(*bigdecimal, i);
    if (end_bit == 1) {
      set_bit_big_mantis(&result, i, 1);
    }
    end_bit = bit;
  }
  bigdecimal->bits[0] = result.bits[0];
  bigdecimal->bits[1] = result.bits[1];
  bigdecimal->bits[2] = result.bits[2];
  bigdecimal->bits[3] = result.bits[3];
  bigdecimal->bits[4] = result.bits[4];
  bigdecimal->bits[5] = result.bits[5];
  bigdecimal->bits[6] = result.bits[6];
  bigdecimal->bits[7] = result.bits[7];
  bigdecimal->bits[8] = result.bits[8];

  return end_bit;
}

int shift_to_right_big(big_decimal *bigdecimal) {
  int start_bit = 0;
  int bit = 0;
  big_decimal result;
  reset_big_decimal(&result);

  for (int i = 287; i >= 0; i--) {
    bit = check_bit_big_mantis(*bigdecimal, i);
    if (start_bit == 1) {
      set_bit_big_mantis(&result, i, 1);
    }
    start_bit = bit;
  }
  bigdecimal->bits[0] = result.bits[0];
  bigdecimal->bits[1] = result.bits[1];
  bigdecimal->bits[2] = result.bits[2];
  bigdecimal->bits[3] = result.bits[3];
  bigdecimal->bits[4] = result.bits[4];
  bigdecimal->bits[5] = result.bits[5];
  bigdecimal->bits[6] = result.bits[6];
  bigdecimal->bits[7] = result.bits[7];
  bigdecimal->bits[8] = result.bits[8];

  return start_bit;
}

int is_less_big_mantis(big_decimal value_1, big_decimal value_2) {
  int result = -1;
  int check_mantis_1 = check_big_mantis(value_1);
  int check_mantis_2 = check_big_mantis(value_2);

  if (check_mantis_1 < check_mantis_2) {
    result = 1;
  } else if (is_equal_big_mantis(value_1, value_2)) {
    result = 0;
  } else if (check_mantis_1 == check_mantis_2) {
    for (int i = check_mantis_1; i >= 0 && result == -1; i--) {
      if (check_bit_big_mantis(value_1, i) < check_bit_big_mantis(value_2, i)) {
        result = 1;
      } else if (check_bit_big_mantis(value_1, i) >
                 check_bit_big_mantis(value_2, i)) {
        result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int is_equal_big_mantis(big_decimal value_1, big_decimal value_2) {
  int result = 1;
  int check_mantis_1 = check_big_mantis(value_1);
  int check_mantis_2 = check_big_mantis(value_2);

  if (check_mantis_1 == check_mantis_2) {
    for (int i = check_mantis_1; i >= 0 && result == 1; i--) {
      if (check_bit_big_mantis(value_1, i) > check_bit_big_mantis(value_2, i)) {
        result = 0;
      } else if (check_bit_big_mantis(value_1, i) <
                 check_bit_big_mantis(value_2, i)) {
        result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int is_greater_big_mantis(big_decimal value_1, big_decimal value_2) {
  int result = 0;
  if (!is_less_big_mantis(value_1, value_2)) {
    if (!is_equal_big_mantis(value_1, value_2)) {
      result = 1;
    }
  }
  return result;
}

int is_greater_or_equal_big_mantis(big_decimal value_1, big_decimal value_2) {
  int result = 0;
  if (!is_less_big_mantis(value_1, value_2)) {
    result = 1;
  }
  return result;
}

void reset_big_decimal(big_decimal *decimal) {
  char *ptr = (char *)decimal;
  for (size_t i = 0; i < sizeof(big_decimal); i++) {
    ptr[i] = 0;
  }
}
#include "s21_decimal.h"

int s21_big_round(big_decimal value, big_decimal *result) {
  big_decimal prec_res;
  reset_big_decimal(&prec_res);

  big_decimal tmp;
  big_decimal isDec = {{10, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal half = {{5, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal remainder1;

  div_big_mantis(value, isDec, &remainder1, &tmp);

  add_big_mantis(value, half, &prec_res);
  *result = prec_res;

  reset_big_decimal(&tmp);
  set_bit_big_mantis(&tmp, 0, 1);

  if (is_equal_big_mantis(half, remainder1)) {
    div_big_mantis(*result, isDec, &remainder1, &prec_res);

    if (check_bit_big_mantis(prec_res, 0) == 1) {
      *result = prec_res;
      sub_big_mantis(prec_res, tmp, result);

      prec_res = *result;
      mul_big_mantis(prec_res, isDec, result);
    }
  }

  return 0;
}

int normalization_exp(big_decimal *value_1, int *exponent) {
  int error = 0;
  s21_decimal multiplier;
  big_decimal multiplier_big;
  reset_decimal(&multiplier);
  reset_big_decimal(&multiplier_big);

  s21_from_int_to_decimal(10, &multiplier);
  mantis_to_big_mantis(multiplier, &multiplier_big);

  big_decimal db_value;
  reset_big_decimal(&db_value);

  int check = check_big_mantis(*value_1);

  big_decimal remainder;

  for (; *exponent > 0 && check > 95; (*exponent)--) {
    s21_big_round(*value_1, &db_value);

    div_big_mantis(db_value, multiplier_big, &remainder, value_1);

    check = check_big_mantis(*value_1);
  }

  if (check > 95) {
    error = 1;
  }

  if (*exponent > 28) {
    error = 2;
  }

  return error;
}

int normalization(s21_decimal val_1, s21_decimal val_2, big_decimal *value_1,
                  big_decimal *value_2, int *exponent) {
  int error = 0;
  if (examination_decimal(val_1) != 0 && examination_decimal(val_2) != 0) {
    error = 1;
  } else {
    reset_big_decimal(value_1);
    reset_big_decimal(value_2);

    mantis_to_big_mantis(val_1, value_1);
    mantis_to_big_mantis(val_2, value_2);

    int exp1 = check_exp(val_1);
    int exp2 = check_exp(val_2);
    s21_decimal multiplier;
    big_decimal multiplier_big;
    reset_decimal(&multiplier);
    reset_big_decimal(&multiplier_big);
    s21_from_int_to_decimal(10, &multiplier);
    mantis_to_big_mantis(multiplier, &multiplier_big);

    big_decimal dop_value;
    reset_big_decimal(&dop_value);

    if (exp1 < exp2) {
      int diff = exp2 - exp1;

      for (int i = 0; i < diff; i++) {
        dop_value = *value_1;
        mul_big_mantis(dop_value, multiplier_big, value_1);
      }
      exp1 = exp2;
    } else if (exp1 > exp2) {
      int diff = exp1 - exp2;

      for (int i = 0; i < diff; i++) {
        dop_value = *value_2;
        mul_big_mantis(dop_value, multiplier_big, value_2);
      }
      exp2 = exp1;
    }

    *exponent = exp1;
  }

  return error;
}

int examination_decimal(s21_decimal decimal) {
  int error = 0;

  int exp = check_exp(decimal);
  int zero = (decimal.bits[3] & 0x0000FFFF);
  int zero_1 = (decimal.bits[3] & 0b01111111000000000000000000000000) >> 24;
  if (zero != 0) {
    error = 1;
  } else if (exp > 28) {
    error = 2;
  } else if (zero_1 != 0) {
    error = 3;
  }
  return error;
}

int check_bit_mantis(s21_decimal decimal, int check) {
  int result = -3;
  if (check >= 0 && check < 32) {
    result = check_bit(decimal.bits[0], check);
  } else if (check >= 32 && check < 64) {
    check = check % 32;
    result = check_bit(decimal.bits[1], check);
  } else if (check >= 64 && check < 96) {
    check = check % 64;
    result = check_bit(decimal.bits[2], check);
  }
  return result;
}

int swap_bit_mantis(s21_decimal *decimal, int check) {
  unsigned one = 0;
  if (check >= 0 && check < 32) {
    one = 1 << check;
    decimal->bits[0] = decimal->bits[0] ^ one;
  } else if (check >= 32 && check < 64) {
    check = check % 32;
    one = 1 << check;
    decimal->bits[1] = decimal->bits[1] ^ one;
  } else if (check >= 64 && check < 96) {
    check = check % 64;
    one = 1 << check;
    decimal->bits[2] = decimal->bits[2] ^ one;
  }
  return 0;
}

int set_bit_mantis(s21_decimal *decimal, int check, int set) {
  if (check_bit_mantis(*decimal, check)) {
    if (set == 0) {
      swap_bit_mantis(decimal, check);
    }
  } else {
    if (set == 1) {
      swap_bit_mantis(decimal, check);
    }
  }
  return 0;
}

int check_sign(s21_decimal decimal) { return check_bit(decimal.bits[3], 31); }

int set_sign(s21_decimal *decimal, int set) {
  if (check_sign(*decimal)) {
    if (set == 0) {
      swap_sign(decimal);
    }
  } else {
    if (set == 1) {
      swap_sign(decimal);
    }
  }
  return 0;
}

int swap_sign(s21_decimal *decimal) {
  unsigned one = 1 << 31;
  decimal->bits[3] = decimal->bits[3] ^ one;
  return 0;
}

int check_exp(s21_decimal decimal) {
  return (decimal.bits[3] & 0x00FF0000) >> 16;
}

int reset_exp(s21_decimal *decimal) {
  int pre_exp = check_exp(*decimal);
  decimal->bits[3] = decimal->bits[3] ^ (pre_exp << 16);
  return 0;
}

int set_exp(s21_decimal *decimal, int exp) {
  int error = -1;
  if (exp >= 0 && exp <= 28) {
    reset_exp(decimal);
    decimal->bits[3] = decimal->bits[3] | (exp << 16);
    error = 0;
  }
  return error;
}

int check_bit(int bit, int check) {
  unsigned one = 1 << check;
  int result = 3;
  if (check >= 0 && check < 32) {
    result = bit & one;
    result = result >> check;
  }
  return abs(result);
}

int check_mantis(s21_decimal decimal) {
  int result = -1;

  for (int i = 0; i < 96; i++) {
    if (check_bit_mantis(decimal, i)) {
      result = i;
    }
  }
  return result;
}

void reset_decimal(s21_decimal *decimal) {
  char *ptr = (char *)decimal;
  for (size_t i = 0; i < sizeof(s21_decimal); i++) {
    ptr[i] = 0;
  }
}
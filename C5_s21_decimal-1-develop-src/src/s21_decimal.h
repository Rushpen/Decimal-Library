#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define S21_INT_MAX 2147483647
#define S21_INT_MIN -2147483648
#define S21_FLOAT_MIN 1E-28
#define S21_FLOAT_MAX 79228162514264337593543950335.00

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[10];
} big_decimal;

typedef struct
{
  unsigned int _zero:16;
  unsigned int exponent:8;
  unsigned int _zero1:7;
  unsigned int sign:1;
} fourth_byte;

// common
int check_mantis(s21_decimal decimal);
int check_bit_mantis(s21_decimal decimal, int check);
int swap_bit_mantis(s21_decimal *decimal, int check);
int set_bit_mantis(s21_decimal *decimal, int check, int set);
int check_bit(int bit, int check);
int byte_field_check(s21_decimal decimal, fourth_byte *fourth);
int byte_field_set(s21_decimal *decimal, fourth_byte fourth);

//operations with big_mantis
int check_bit_big_mantis(big_decimal big_decimal, int check);
int swap_bit_big_mantis(big_decimal *big_decimal, int check);
int set_bit_big_mantis(big_decimal *big_decimal, int check, int set);
int check_big_mantis(big_decimal decimal);
int shift_to_left_big(big_decimal *bigdecimal);
int shift_to_right_big(big_decimal *bigdecimal);
int mantis_to_big_mantis(s21_decimal decimal, big_decimal *big_decimal);
int is_less_big_mantis(big_decimal value_1, big_decimal value_2);
int is_equal_big_mantis(big_decimal value_1, big_decimal value_2);
int is_greater_big_mantis(big_decimal value_1, big_decimal value_2);
int is_greater_or_equal_big_mantis(big_decimal value_1, big_decimal value_2);
void reset_big_decimal(big_decimal *decimal);
int big_mantis_to_mantis(s21_decimal *decimal, big_decimal bigdecimal, int exp, int sign);

int normalization (s21_decimal val_1, s21_decimal val_2, big_decimal *value_1, big_decimal *value_2, int *exponent);
int normalization_exp (big_decimal *value_1, int *exponent);
int examination_decimal(s21_decimal decimal);

int check_sign(s21_decimal decimal);
int swap_sign(s21_decimal *decimal);
int set_sign(s21_decimal *decimal, int set);

int check_exp(s21_decimal decimal);
int reset_exp(s21_decimal *decimal);
int set_exp(s21_decimal *decimal, int exp);

int shift_to_left(s21_decimal *decimal);
int shift_to_right(s21_decimal *decimal);

void reset_decimal(s21_decimal *decimal);

// +
int add_big_mantis(big_decimal value_1, big_decimal value_2, big_decimal *result);
int add_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result, int *exponent);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// -
int sub_big_mantis(big_decimal value_1, big_decimal value_2, big_decimal *result);
int sub_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result, int *exponent, int *sign);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// *
int mul_big_mantis(big_decimal value_1, big_decimal value_2, big_decimal *result);
int mul_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result, int *exponent);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// : or /
int div_big_mantis(big_decimal value_1, big_decimal value_2, big_decimal *remainder, big_decimal *result);
int div_man(s21_decimal value_1, s21_decimal value_2, big_decimal *big_result,
            int *exponent);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);


int is_less_mantis(s21_decimal value_1, s21_decimal value_2);
int is_less_or_equal_mantis(s21_decimal value_1, s21_decimal value_2);
int is_greater_mantis(s21_decimal value_1, s21_decimal value_2);
int is_greater_or_equal_mantis(s21_decimal value_1, s21_decimal value_2);
int is_equal_mantis(s21_decimal value_1, s21_decimal value_2);
int is_not_equal_mantis(s21_decimal value_1, s21_decimal value_2);

//Comparison operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

//Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);


#endif

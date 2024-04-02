#include <check.h>
#include <stdlib.h>

#include "s21_another_test.h"
#include "s21_arithmetic_test.h"
#include "s21_comparison_test.h"
#include "s21_convertor_test.h"

int main() {
  int failed_count = 0;
  Suite* suite1 = s21_arithmetic_suite_create();
  Suite* suite2 = s21_comparison_suite_create();
  Suite* suite3 = s21_convertor_suite_create();
  Suite* suite4 = s21_another_suite_create();

  SRunner* suite_runner1 = srunner_create(suite1);
  SRunner* suite_runner2 = srunner_create(suite2);
  SRunner* suite_runner3 = srunner_create(suite3);
  SRunner* suite_runner4 = srunner_create(suite4);

  srunner_run_all(suite_runner1, CK_NORMAL);
  srunner_run_all(suite_runner2, CK_NORMAL);
  srunner_run_all(suite_runner3, CK_NORMAL);
  srunner_run_all(suite_runner4, CK_NORMAL);

  failed_count += srunner_ntests_failed(suite_runner1);
  failed_count += srunner_ntests_failed(suite_runner2);
  failed_count += srunner_ntests_failed(suite_runner3);
  failed_count += srunner_ntests_failed(suite_runner4);

  srunner_free(suite_runner1);
  srunner_free(suite_runner2);
  srunner_free(suite_runner3);
  srunner_free(suite_runner4);

  printf("Fail = %d\n", failed_count);

  return 0;
}
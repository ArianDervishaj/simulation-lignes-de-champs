#include "vec2.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct _test_result {
  bool passed;
  const char *name;
} test_result;

typedef test_result (*unit_test_t)(void);

void print_in_color(char *color, char *text) {
  printf("\033%s", color);
  printf("%s", text);
  printf("\033[0m");
}
void print_in_red(char *text) { print_in_color("[0;31m", text); }
void print_in_green(char *text) { print_in_color("[0;32m", text); }

bool dbl_eq(double a, double b) { return fabs(a - b) < 1e-6; }

/*
 *
 * Write your tests here
 *
 */
/*
vec2 vec2_create(double x_, double y_); -- Ok
vec2 vec2_create_zero(); -- Ok
vec2 vec2_add(vec2 lhs, vec2 rhs); -- Ok
vec2 vec2_sub(vec2 lhs, vec2 rhs); -- Ok
vec2 vec2_mul(double scalar, vec2 lhs); -- Ok
double vec2_dot(vec2 lhs, vec2 rhs); -- Ok
double vec2_norm_sqr(vec2 v); -- Ok
double vec2_norm(vec2 v); -- Ok
vec2 vec2_normalize(vec2 v); -- Ok
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps);
coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height);
*/
const double u_x[] = {1.25, 3.53, 2.64, 8.8};
const double u_y[] = {3.42, 7.22, 5.32, 2.44};
const double v_x[] = {4.32, 6.21, 7.42, 9.32};
const double v_y[] = {5.22, 3.56, 8.65, 6.44};
const uint32_t nb_tests = sizeof(u_x) / sizeof(double);

test_result t_vec2_create_0() {
  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 v = vec2_create(u_x[i], u_y[i]);
    if (u_x[i] != v.x || u_y[i] != v.y) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_create 0"};
}
test_result t_vec2_create_zero_0() {
  vec2 v = vec2_create_zero();

  return (test_result){.passed = v.x == 0.0 && v.y == 0.0,
                       .name = "Test vec2_create_zero 0"};
}
test_result t_vec2_add_0() {
  double r_x[] = {5.57, 9.74, 10.06, 18.12};
  double r_y[] = {8.64, 10.78, 13.97, 8.88};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 v = vec2_create(v_x[i], v_y[i]);
    vec2 r = vec2_add(u, v);
    if (!(dbl_eq(r.x, r_x[i]) && dbl_eq(r.y, r_y[i]))) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_add 0"};
}
test_result t_vec2_sub_0() {
  double r_x[] = {-3.07, -2.68, -4.78, -0.52};
  double r_y[] = {-1.80, 3.66, -3.33, -4.00};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 v = vec2_create(v_x[i], v_y[i]);
    vec2 r = vec2_sub(u, v);
    if (!(dbl_eq(r.x, r_x[i]) && dbl_eq(r.y, r_y[i]))) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_sub 0"};
}
test_result t_vec2_mul_0() {
  double r_x[] = {5.40, 21.9213, 19.5888, 82.016};
  double r_y[] = {14.7744, 44.8362, 39.4744, 22.740800};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    double alpha = v_x[i];
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 r = vec2_mul(alpha, u);
    if (!(dbl_eq(r.x, r_x[i]) && dbl_eq(r.y, r_y[i]))) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_mul 0"};
}
test_result t_vec2_dot_0() {
  double r[] = {23.2524, 47.6245, 65.6068, 97.7296};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 v = vec2_create(v_x[i], v_y[i]);
    double res = vec2_dot(u, v);
    if (!dbl_eq(res, r[i])) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_dot 0"};
}
test_result t_vec2_norm_sqr_0() {
  double r[] = {13.2589, 64.5893, 35.272, 83.3936};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    double res = vec2_norm_sqr(u);
    if (!dbl_eq(res, r[i])) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_norm_sqr 0"};
}
test_result t_vec2_norm_0() {
  double r[] = {3.641277, 8.036747, 5.939023, 9.132010};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    double res = vec2_norm(u);
    if (!dbl_eq(res, r[i])) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_norm 0"};
}
test_result t_vec2_normalize_0() {
  double r_x[] = {0.343286, 0.439232, 0.444518, 0.963643};
  double r_y[] = {0.939231, 0.898373, 0.895770, 0.267192};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 r = vec2_normalize(u);
    if (!(dbl_eq(r.x, r_x[i]) && dbl_eq(r.y, r_y[i]))) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_normalize 0"};
}
test_result t_vec2_is_approx_equal_0() {
  bool r[] = {true, true, false, false};

  double t_x[] = {u_x[0], u_x[1] + 1e-4, u_x[2] + 15.0, u_x[3] + 1e-2};
  double t_y[] = {u_y[0], u_y[1] - 1e-4, u_y[2] + 15.0, u_y[3] + 1e-2};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 u = vec2_create(u_x[i], u_y[i]);
    vec2 t = vec2_create(t_x[i], t_y[i]);
    if (vec2_is_approx_equal(u, t, 1e-3) != r[i]) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_is_approx_equal 0"};
}
test_result t_vec2_to_coordinates_0() {
  uint32_t height = 300;
  uint32_t width = 100;
  double t_x[] = {0.25, 0.5, 0.75, 1};
  double t_y[] = {0, 1.0 / 3.0, 2.0 / 3.0, 1};
  uint32_t r_col[] = {62, 74, 87, 99};
  uint32_t r_row[] = {150, 199, 249, 299};

  bool passed = true;
  for (uint32_t i = 0; i < nb_tests; i++) {
    vec2 t = vec2_create(t_x[i], t_y[i]);
    coordinates r = vec2_to_coordinates(t, width, height);
    if (r.row != r_row[i] || r.column != r_col[i]) {
      passed = false;
      break;
    }
  }

  return (test_result){.passed = passed, .name = "Test vec2_to_coordinates 0"};
}
// Add or remove your test function name here
const unit_test_t tests[] = {t_vec2_create_0,        t_vec2_create_zero_0,
                             t_vec2_add_0,           t_vec2_sub_0,
                             t_vec2_mul_0,           t_vec2_dot_0,
                             t_vec2_norm_sqr_0,      t_vec2_norm_0,
                             t_vec2_normalize_0,     t_vec2_is_approx_equal_0,
                             t_vec2_to_coordinates_0};

int main() {
  uint32_t nb_tests = sizeof(tests) / sizeof(unit_test_t);
  char message[256];
  bool all_passed = true;

  for (uint32_t i = 0; i < nb_tests; i++) {
    printf("Running test n°%d: ...\n", i);
    test_result r = tests[i]();
    if (r.passed) {
      sprintf(message, "\t- %s : OK", r.name);
      print_in_green(message);
    } else {
      all_passed = false;
      sprintf(message, "\t- %s : FAILED", r.name);
      print_in_red(message);
    }
    printf("\n");
  }
  if (all_passed)
    print_in_green("\nTests suite result : OK\n");
  else
    print_in_red("\nTests suite result : FAILED\n");
}
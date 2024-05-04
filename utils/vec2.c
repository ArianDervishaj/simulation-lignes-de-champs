#include "vec2.h"
#include <stdlib.h>

/// Create a 2d vector.
/// @param x_ The first component.
/// @param y_ The second component.
/// @return The newly created vector.
vec2 vec2_create(double x_, double y_) {
  vec2 vector;
  vector.x = x_;
  vector.y = y_;

  return vector;
}

double rand_one() { return (double)rand() / (double)RAND_MAX; }

/// Create a zero 2d vector.
/// @return The newly created zero vector.
vec2 vec2_create_zero() {
  vec2 vector = vec2_create(rand_one(), rand_one());
  return vector;
}


vec2 vec2_create_random() {
  vec2 vector = vec2_create(rand_one(), rand_one());
  return vector;
}

/// Add two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The sum in a new vector.
vec2 vec2_add(vec2 lhs, vec2 rhs) {
  vec2 vector_res;
  vector_res.x = lhs.x + rhs.x;
  vector_res.y = lhs.y + rhs.y;

  return vector_res;
}

/// Substract two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The difference in a new vector.
vec2 vec2_sub(vec2 lhs, vec2 rhs) {
  vec2 vector_res;
  vector_res.x = lhs.x - rhs.x;
  vector_res.y = lhs.y - rhs.y;

  return vector_res;
}

/// Multiply a vector by a scalar.
/// @param scalar The left operand, a scalar.
/// @param rhs The right operand, a vector.
/// @return The product in a new vector.
vec2 vec2_mul(double scalar, vec2 rhs) {
  vec2 vector;
  vector.x = scalar * rhs.x;
  vector.y = scalar * rhs.y;

  return vector;
}

/// Compute the dot product (scalar product) between two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The dot product.
double vec2_dot(vec2 lhs, vec2 rhs) {
  double res = (lhs.x * rhs.x) + (lhs.y * rhs.y);

  return res;
}

/// Compute the square of the euclidean norm of a given vector.
/// @param v The vector.
/// @return The square of the norm.
double vec2_norm_sqr(vec2 v) {
  double res = pow(v.x, 2) + pow(v.y, 2);
  return res;
}

/// Compute the euclidean norm of a given vector.
/// @param v The vector.
/// @return The norm.
double vec2_norm(vec2 v) {
  double res = sqrt(vec2_norm_sqr(v));
  return res;
}

/// Compute the normalization of a given vector.
/// @param v The vector.
/// @return The new normalized vector.
vec2 vec2_normalize(vec2 v) {
  vec2 vector_res;
  double scal = 1 / vec2_norm(v);
  vector_res.x = scal * v.x;
  vector_res.y = scal * v.y;

  return vector_res;
}

/// Create a perpendicular vector.
/// @param v The vector.
/// @return The new perpendicular vector.
vec2 vec2_perpendicular(vec2 v) {
  vec2 vector_res;
  vector_res.x = -1 * v.y;
  vector_res.y = v.x;

  return vector_res;
}

/// Check whether two vectors are approximately equals within a given tolerance.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @param eps The tolerance.
/// @return true if vector are approximately equal, false otherwise.
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps) {
  if (lhs.x <= rhs.x + eps && lhs.x >= rhs.x - eps && lhs.y <= rhs.y + eps &&
      lhs.y >= rhs.y - eps) {
    return true;
  } else {
    return false;
  }
}

/// Compute the coordinates of a 2d vector (with components between -1 and 1)
/// in a given screen matrix.
/// @param v The 2d vector.
/// @param width The screen width.
/// @param height The screen height.
/// @return The coordinates (row, column).
coordinates_t vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height) {
  coordinates_t result;
  result.row = (uint32_t)((v.y / 600e9) * (height)) + height / 2;
  result.column = (uint32_t)((v.x / 600e9) * (width)) + width / 2;

  return result;
}

/// Print a vector in the standard output.
/// @param v The vector.
void vec2_print(vec2 v) { printf("x = %g, y = %g\n", v.x, v.y); }
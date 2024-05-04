#ifndef _UTILS_H_
#define _UTILS_H_

#include "gfx/gfx.h"
#include "vec2.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#define SCREEN_WIDTH 1200  ///< Width of the simulation screen in pixels.
#define SCREEN_HEIGHT 1000 ///< Height of the simulation screen in pixels.
#define EPS 1e-3           ///< Small value.

extern const double K; ///< Coulomb's constant.
extern const double E;

/**
 * @brief Represents an electric charge.
 * @param q Magnitude of the charge.
 * @param pos Position of the charge.
 */
typedef struct {
  double q;
  vec2 pos;
} charge_t;

/**
 * @brief Creates and returns coordinates for a given grid position.
 * @param row_ Row index.
 * @param column_ Column index.
 * @return coordinates_t Coordinates object.
 */
coordinates_t coordinates_create(int row_, int column_);

/**
 * @brief Transforms simulation space position to screen coordinates.
 * @param width Screen width.
 * @param height Screen height.
 * @param x0, x1 x-boundaries of simulation space.
 * @param y0, y1 y-boundaries of simulation space.
 * @param pos Position in simulation space.
 * @return coordinates_t Screen coordinates.
 */
coordinates_t position_to_coordinates(int width, int height, double x0,
                                      double x1, double y0, double y1,
                                      vec2 pos);

/**
 * @brief Creates a positive charge with a specified magnitude and position.
 * @param q Charge magnitude.
 * @param pos Charge position.
 * @return charge_t Charge object.
 */
charge_t charge_create(double q, vec2 pos);

/**
 * Generates a positive charge with random magnitude and position.
 * @return charge_t Charge object.
 */
charge_t charge_create_random_neg();

/**
 * Generates a negative charge by inverting the charge of a positive one.
 * @return charge_t Charge object.
 */
charge_t charge_create_random_pos();

/**
 * Allocates and initializes an array of charges with specified numbers of
 * positive and negative charges.
 * @param num_charges_neg Number of negative charges to generate.
 * @param num_charges_pos Number of positive charges to generate.
 * @return charge_t* Pointer to the first charge in the dynamically allocated
 * array.
 */
charge_t *generate_random_charges(int num_charges_neg, int num_charges_pos);

/**
 * @brief Draws a line between two points on the graphics context.
 * @param ctxt Graphics context.
 * @param p0 Start point.
 * @param p1 End point.
 * @param color Line color.
 */
void gfx_draw_line(struct gfx_context_t *ctxt, coordinates_t p0,
                   coordinates_t p1, uint32_t color);

/**
 * Draws horizontal line on the graphics context.
 * @param ctxt Graphics context.
 * @param sy y-coordinate for the line.
 * @param sx1 x-coordinate for the start of the line.
 * @param sx2 x-coordinate for the end of the line.
 * @param color Color of the line.
 */
void draw_horizontal_line(struct gfx_context_t *ctxt, int sy, int sx1, int sx2,
                          uint32_t color);

/**
 * @brief Draws a circle on the graphics context.
 * @param ctxt Graphics context.
 * @param c Circle center.
 * @param r Radius.
 * @param color Circle color.
 */
void gfx_draw_circle(struct gfx_context_t *ctxt, coordinates_t c, uint32_t r,
                     uint32_t color);

/**
 * @brief Computes the electric field at a point due to a charge.
 * @param c Charge causing the field.
 * @param p Point of interest.
 * @param e Electric field vector.
 * @return bool True if computation successful, false otherwise.
 */
bool compute_e(charge_t c, vec2 p, vec2 *e);

/**
 * @brief Computes normalized sum of electric fields at a point due to multiple
 * charges.
 * @param charges Array of charges.
 * @param num_charges Number of charges.
 * @param p Point of interest.
 * @param e Resulting electric field vector.
 * @return bool True if computation successful, false otherwise.
 */
bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p,
                                vec2 *e);

/**
 * @brief Checks if a position is within the simulation boundaries.
 * @param pos Position to check.
 * @param x0, x1 x-boundaries of simulation space.
 * @param y0, y1 y-boundaries of simulation space.
 * @return bool True if position is within boundaries, false otherwise.
 */
bool is_in_universe(vec2 pos, double x0, double x1, double y0, double y1);

/**
 * @brief Checks that a point is not too close to a set of charges
 * @param pos the position of our point of interest
 * @param charges Array of charges.
 * @param num_charges Number of charges.
 * @return bool True if pos is far enough from the charges False otherwise.
 */
bool check_distance_from_charges(vec2 pos, charge_t *charges, int num_charges);

/**
 * @brief Computes and draws a field line from a starting position.
 * @param ctxt Graphics context.
 * @param charges Array of charges.
 * @param num_charges Number of charges.
 * @param dx Differential distance.
 * @param pos0 Starting position.
 * @param x0, x1 x-boundaries of simulation space.
 * @param y0, y1 y-boundaries of simulation space.
 * @return bool True if field line drawn successfully, false otherwise.
 */
bool draw_field_line(struct gfx_context_t *ctxt, charge_t *charges,
                     int num_charges, double dx, double x0, double x1,
                     double y0, double y1);

/**
 * @brief Draws all charges within given universe boundaries.
 * @param context Graphics context.
 * @param charges Array of charges.
 * @param num_charges Number of charges.
 * @param x0, x1 x-boundaries of simulation space.
 * @param y0, y1 y-boundaries of simulation space.
 */
void draw_charges(struct gfx_context_t *context, charge_t *charges,
                  int num_charges, double x0, double x1, double y0, double y1);

/**
 * @brief Draw the segment between the current point and the next one.
 * @param context Graphics context.
 * @param charges Array of charges.
 * @param num_charges Number of charges.
 * @param dx Step between two points
 * @param pos Vec2 of the current position
 * @param x0, x1 x-boundaries of simulation space.
 * @param y0, y1 y-boundaries of simulation space.
 */
bool draw_next_point(struct gfx_context_t *ctxt, charge_t *charges,
                     int num_charges, double dx, vec2 *pos, double x0,
                     double x1, double y0, double y1, u_int32_t color);

#endif

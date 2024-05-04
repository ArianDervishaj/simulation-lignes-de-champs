#include "utils.h"
#include "gfx/gfx.h"
#include "vec2.h"
#include <SDL2/SDL_assert.h>
#include <stdint.h>
#include <stdio.h>

const double K = 8.988e9;
const double E = 1.602e-19;

coordinates_t coordinates_create(int row_, int column_) {
  coordinates_t c = {.row = row_, .column = column_};
  return c;
}

coordinates_t position_to_coordinates(int width, int height, double x0,
                                      double x1, double y0, double y1,
                                      vec2 pos) {
  double dx = x1 - x0;
  double dy = y1 - y0;
  return coordinates_create((int)round(height * (pos.y - y0) / dy),
                            (int)round(width * (pos.x - x0) / dx));
}

charge_t charge_create(double q, vec2 pos) {
  charge_t c = {.q = q, .pos = pos};
  return c;
}

charge_t charge_create_random_pos() {
  double q = (rand() % 4 + 1) * E;
  q = (q == 0 ? 5 : q);
  charge_t c = {.q = q, .pos = vec2_create_random()};
  return c;
}

charge_t charge_create_random_neg() {
  charge_t c = charge_create_random_pos();
  c.q = c.q * -1;
  return c;
}

charge_t *generate_random_charges(int num_charges_neg, int num_charges_pos) {
  int num_charges = num_charges_neg + num_charges_pos;
  charge_t *charges = calloc(num_charges, sizeof(charge_t));
  for (int i = 0; i < num_charges_pos; i++) {
    charges[i] = charge_create_random_pos();
  }
  for (int i = num_charges_pos; i < num_charges; i++) {
    charges[i] = charge_create_random_neg();
  }

  return charges;
}

void gfx_draw_line(struct gfx_context_t *ctxt, coordinates_t p0,
                   coordinates_t p1, uint32_t color) {
  int dy = p1.row - p0.row;
  int dx = p1.column - p0.column;
  int m_dx = p0.column - p1.column;

  if (dy >= 0) {    // Octants supérieurs
    if (dy <= dx) { // 1er octant
      int a = 2 * dy;
      int e = 0;
      int y = p0.row;

      for (int64_t x = p0.column; x <= p1.column; x++) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e >= dx) {
          y++;
          e -= 2 * dx;
        }
      }
    } else if (dy > dx && dy >= m_dx) { // 2ème octant
      int a = 2 * dx;
      int e = 0;
      int x = p0.column;

      for (int64_t y = p0.row; y <= p1.row; y++) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e >= dy) {
          x++;
          e -= 2 * dy;
        }
      }
    } else if (dy < m_dx) { // 3ème octant
      int a = 2 * (p0.row - p1.row);
      int e = 0;
      int m_dy = p0.row - p1.row;
      int x = p0.column;

      for (int64_t y = p0.row; y <= p1.row; y++) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e <= m_dy) {
          x--;
          e += 2 * dx;
        }
      }
    } else { // 4ème octant
      int a = 2 * (p1.row - p0.row);
      int e = 0;
      int x = p0.column;

      for (int64_t y = p0.row; y <= p1.row; y++) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e >= m_dx) {
          x++;
          e += 2 * dx;
        }
      }
    }
  } else {
    if (-dy <= dx) { // 8ème octant
      int a = 2 * (-dy);
      int e = 0;
      int y = p0.row;

      for (int64_t x = p0.column; x <= p1.column; x++) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e <= m_dx) {
          y--;
          e += 2 * dx;
        }
      }
    } else { // Tous les autres octants
      int a = 2 * (-dx);
      int e = 0;
      int x = p0.column;

      for (int64_t y = p0.row; y >= p1.row; y--) {
        gfx_putpixel(ctxt, x, y, color);
        e += a;
        if (e <= dy) {
          x++;
          e += 2 * dy;
        }
      }
    }
  }
}

void draw_horizontal_line(struct gfx_context_t *ctxt, int sy, int sx1, int sx2,
                          uint32_t color) {
  coordinates_t p0 = {.column = sx1, .row = sy};
  coordinates_t p1 = {.column = sx2, .row = sy};
  gfx_draw_line(ctxt, p0, p1, color);
}

void gfx_draw_circle(struct gfx_context_t *ctxt, coordinates_t c, uint32_t r,
                     uint32_t color) {
  int x = 0;
  int y = r;
  int d = 3 - 2 * r;

  while (y >= x) {
    // Draw horizontal lines from -x to x for each y
    draw_horizontal_line(ctxt, c.row + y, c.column - x, c.column + x, color);
    draw_horizontal_line(ctxt, c.row - y, c.column - x, c.column + x, color);
    draw_horizontal_line(ctxt, c.row + x, c.column - y, c.column + y, color);
    draw_horizontal_line(ctxt, c.row - x, c.column - y, c.column + y, color);

    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
  }
}

bool compute_e(charge_t c, vec2 p, vec2 *e) {
  if (c.pos.x == 0 && c.pos.y == 0) {
    return false;
  }

  if (p.x == 0 && p.y == 0) {
    return false;
  }

  vec2 qP = vec2_sub(c.pos, p);
  double r = vec2_norm(qP);

  if (r < EPS) {
    return false;
  }

  double res = K * c.q / (r * r);
  *e = vec2_mul(res, vec2_normalize(qP));

  return true;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p,
                                vec2 *e) {
  // Resultant field force
  vec2 total_e = vec2_create(0, 0);

  for (int i = 0; i < num_charges; i++) {

    bool is_ok = compute_e(charges[i], p, e);

    if (!is_ok) {
      return false;
    }

    total_e = vec2_add(total_e, *e);
  }

  *e = vec2_normalize(total_e);

  return true;
}

bool is_in_universe(vec2 pos, double x0, double x1, double y0, double y1) {
  return (pos.x >= x0 && pos.x <= x1 && pos.y >= y0 && pos.y <= y1);
}

bool check_distance_from_charges(vec2 pos, charge_t *charges, int num_charges) {
  for (int i = 0; i < num_charges; i++) {
    vec2 vect_distance = vec2_sub(pos, charges[i].pos);
    double distance_norm = vec2_norm(vect_distance);

    if (distance_norm < EPS) {
      return false;
    }
  }
  return true;
}

bool draw_next_point(struct gfx_context_t *ctxt, charge_t *charges,
                     int num_charges, double dx, vec2 *pos, double x0,
                     double x1, double y0, double y1, uint32_t color) {

  vec2 field_normalized;
  bool draw =
      compute_total_normalized_e(charges, num_charges, *pos, &field_normalized);
  if (draw) {
    vec2 delta_pos = vec2_mul(dx, field_normalized);
    vec2 pos_next = vec2_add(*pos, delta_pos);

    // Check if pos_next is within the universe bounds and not too close
    // to the charges
    draw = is_in_universe(pos_next, x0, x1, y0, y1) &&
           check_distance_from_charges(pos_next, charges, num_charges);

    // Draw line if all conditions are met
    if (draw) {
      coordinates_t pos_coord = position_to_coordinates(
          SCREEN_WIDTH, SCREEN_HEIGHT, x0, x1, y0, y1, *pos);
      coordinates_t pos_next_coord = position_to_coordinates(
          SCREEN_WIDTH, SCREEN_HEIGHT, x0, x1, y0, y1, pos_next);
      gfx_draw_line(ctxt, pos_coord, pos_next_coord, color);
      // Move to the next point
      *pos = pos_next;
    }
  }
  return draw;
}

bool draw_field_line(struct gfx_context_t *ctxt, charge_t *charges,
                     int num_charges, double dx, double x0, double x1,
                     double y0, double y1) {

  // check that pos0 is not too close from one of the charge

  vec2 pos0 = vec2_create_random();

  if (!check_distance_from_charges(pos0, charges, num_charges)) {

    return false;
  }

  vec2 pos = pos0;
  bool draw = true;

  // draw in one direction
  while (draw) {
    draw = draw_next_point(ctxt, charges, num_charges, dx, &pos, x0, x1, y0, y1,
                           COLOR_GREEN);
  }

  // draw in the other direction
  ;
  pos = pos0;
  draw = true;
  while (draw) {
    draw = draw_next_point(ctxt, charges, num_charges, -1 * dx, &pos, x0, x1,
                           y0, y1, COLOR_WHITE);
  }
  return true;
}

void draw_charges(struct gfx_context_t *ctxt, charge_t *charges,
                  int num_charges, double x0, double x1, double y0, double y1) {

  for (int i = 0; i < num_charges; ++i) {
    coordinates_t screenPos = position_to_coordinates(
        SCREEN_WIDTH, SCREEN_HEIGHT, x0, x1, y0, y1, charges[i].pos);

    int radius = (fabs(charges[i].q / E)) * 8;
    int icon = radius / 2 - radius / 4;
    // Draw the charge as a circle
    if (charges[i].q > 0) {
      // Draw a plus sign
      gfx_draw_circle(ctxt, screenPos, radius, COLOR_BLUE);
      for (int line = -icon; line <= icon; ++line) {
        gfx_putpixel(ctxt, screenPos.column + line, screenPos.row, COLOR_WHITE);
        gfx_putpixel(ctxt, screenPos.column, screenPos.row + line, COLOR_WHITE);
      }
    } else {
      gfx_draw_circle(ctxt, screenPos, radius, COLOR_RED);
      // Draw a minus sign
      for (int line = -icon; line <= icon; ++line) {
        gfx_putpixel(ctxt, screenPos.column + line, screenPos.row, COLOR_WHITE);
      }
    }
  }
}

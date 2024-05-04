#include "utils/gfx/gfx.h"
#include "utils/utils.h"
#include "utils/vec2.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Usage : %s NUMBER_OF_CHARGES_POS NUMBER_OF_CHARGES_NEG "
           "NUMBER_OF_FIELD_LINES \n",
           argv[0]);
    return EXIT_FAILURE;
  }

  int num_charges_pos = atoi(argv[1]);
  int num_charges_neg = atoi(argv[2]);
  int num_field_lines = atoi(argv[3]);
  int num_charges = num_charges_neg + num_charges_pos;

  srand(time(NULL));
  struct gfx_context_t *ctxt =
      gfx_create("Particules", SCREEN_WIDTH, SCREEN_HEIGHT);
  if (!ctxt) {
    fprintf(stderr, "Graphics initialization failed!\n");
    return EXIT_FAILURE;
  }

  charge_t *charges = generate_random_charges(num_charges_neg, num_charges_pos);

  double dx =
      1 / sqrt(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT);

  for (int i = 0; i < num_field_lines; i++) {

    draw_field_line(ctxt, charges, num_charges, dx, 0, 1, 0, 1);
  }

  draw_charges(ctxt, charges, num_charges, 0, 1, 0, 1);

  gfx_present(ctxt);
  while (true) {
    if (gfx_keypressed() == SDLK_ESCAPE) {
      break;
    }
  }

  free(charges);
  gfx_destroy(ctxt);
  return EXIT_SUCCESS;
}
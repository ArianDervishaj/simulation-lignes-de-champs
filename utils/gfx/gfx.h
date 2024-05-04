#ifndef _GFX_H_
#define _GFX_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define MAKE_COLOR(r, g, b)                                                    \
  ((uint32_t)b | ((uint32_t)g << 8) | ((uint32_t)r << 16))

#define COLOR_GET_B(color) (color & 0xff)
#define COLOR_GET_G(color) ((color >> 8) & 0xff)
#define COLOR_GET_R(color) ((color >> 16) & 0xff)

#define COLOR_BLACK 0x00000000
#define COLOR_RED 0x00FF0000
#define COLOR_GREEN 0x0000FF00
#define COLOR_BLUE 0x000000FF
#define COLOR_WHITE 0x00FFFFFF
#define COLOR_YELLOW 0x00FFFF00

struct gfx_context_t {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  uint32_t *pixels;
  uint32_t width;
  uint32_t height;
};

extern void gfx_putpixel(struct gfx_context_t *ctxt, uint32_t column,
                         uint32_t row, uint32_t color);
extern void gfx_clear(struct gfx_context_t *ctxt, uint32_t color);
extern struct gfx_context_t *gfx_create(char *text, uint32_t width,
                                        uint32_t height);
extern void gfx_destroy(struct gfx_context_t *ctxt);
extern void gfx_present(struct gfx_context_t *ctxt);
extern SDL_Keycode gfx_keypressed();

#endif

#ifndef VRAM_H
#define VRAM_H

#include <stdint.h>
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE (8 * 8 * 2)

typedef uint16_t tile_line;
typedef struct tile {
  tile_line lines[8];
} tile;

tile* get_tile(uint8_t block, uint8_t y, uint8_t x);
uint8_t get_pix(tile* t, uint8_t y, uint8_t x);

#endif /* !VRAM_H */

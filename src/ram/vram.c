#include "vram.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

#define BLOCK0 0x8000
#define BLOCK1 0x8800
#define BLOCK2 0x9000

static uint16_t get_block_addr(uint8_t b) {
  switch (b) {
  case 0:
    return BLOCK0;
  case 1:
    return BLOCK1;
  case 2:
    return BLOCK2;
  default:
    printerr("Error, weird block requested: %d\n", b);
    exit(1);
    break;
  }
}

tile *get_tile(uint8_t block, uint8_t y, uint8_t x) {
}

uint8_t get_pix(tile *t, uint8_t y, uint8_t x);

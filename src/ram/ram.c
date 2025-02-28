#include "ram/ram.h"
#include <assert.h>

uint8_t ram[RAM_SIZE];

uint8_t *get_ram_8ptr(uint16_t pos) {
  assert(pos < RAM_SIZE);
  return (uint8_t *)(ram + pos);
}
uint16_t *get_ram_16ptr(uint16_t pos) {
  assert(pos < RAM_SIZE - 1);
  return (uint16_t *)(ram + pos);
}

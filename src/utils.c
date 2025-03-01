#include "utils.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

void printerr(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

void wait_for_input() {
#ifndef NDEBUG
  (void)getchar();
#endif
}

// Assumes little endian
void printBits(uint8_t byte) {
#ifndef NDEBUG
  for (int i = 7; i >= 0; i--) {
    if (byte & (1 << i))
      putc('1', stdout);
    else
      putc('0', stdout);
  }
#endif
}

uint16_t combine_u16(uint8_t x, uint8_t y)
{
  uint16_t r = x;
  r <<= 8;
  r += y;
  return r;
}

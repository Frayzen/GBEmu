#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
void printerr(const char *fmt, ...);
void wait_for_input();
void printBits(uint8_t byte);

uint16_t combine_u16(uint8_t x, uint8_t y);

#define CASSERT(condition) typedef char name[(condition) ? 1 : -1];
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

#define MAX_UINT4 0x0F
#define MAX_UINT8 0xFF
#define MAX_UINT16 0xFFFF

#endif /* !UTILS_H */

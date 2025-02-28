#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
void printerr(const char *fmt, ...);
void wait_for_input();
void printBits(uint8_t byte);

#define CASSERT(condition) typedef char name[(condition) ? 1 : -1];
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif /* !UTILS_H */

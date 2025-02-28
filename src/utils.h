#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
void printerr(const char *fmt, ...);
void wait_for_input();
void printBits(uint8_t byte);

#define CASSERT(condition) void check##__FILE__##__LINE__(){(void)sizeof(char[1 - 2*!(condition)]);}

#endif /* !UTILS_H */

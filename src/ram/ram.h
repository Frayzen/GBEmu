#ifndef RAM_H
#define RAM_H

#include <stdint.h>
#define RAM_SIZE 0xFFFF

extern uint8_t ram[RAM_SIZE];

uint8_t *get_ram_8ptr(uint16_t pos);
uint16_t *get_ram_16ptr(uint16_t pos);

#endif /* !RAM_H */

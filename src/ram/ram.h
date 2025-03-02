#ifndef RAM_H
#define RAM_H

#include <stdint.h>
#define RAM_SIZE 0xFFFF

// ROM Bank 0
#define ROM0_START 0x0000
#define ROM0_END 0x3FFF

// ROM Bank 1 
#define ROM1_START 0x4000
#define ROM1_END 0x7FFF

// Video RAM
#define VRAM_START 0x8000
#define VRAM_END 0x9FFF

// External RAM
#define EXT_RAM_START 0xA000
#define EXT_RAM_END 0xBFFF

// Work RAM
#define WRAM_START 0xC000
#define WRAM_END 0xDFFF


// Object attribute memory
#define OAM_START 0xFE00
#define OAM_END 0xFE9F

// IO/Registers
#define IOREG_START 0xFF00
#define IOREG_END 0xFF7F

// High RAM
#define HRAM_START 0xFF80
#define HRAM_END 0xFFFE


extern uint8_t ram[RAM_SIZE];

uint8_t *get_ram_8ptr(uint16_t pos);
uint16_t *get_ram_16ptr(uint16_t pos);

#endif /* !RAM_H */

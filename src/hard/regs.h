#ifndef REGS_H
#define REGS_H

#include "utils.h"
#include <stdint.h>

#define HIGH(Reg) ((&Reg) & 0xF0)
#define LOW(Reg) ((Reg) & 0x0F)

#define Z_FLG (1 << 7)
#define N_FLG (1 << 6)
#define H_FLG (1 << 5)
#define C_FLG (1 << 4)

#define GET_FLG(F) (regs8->f & (F))
#define SET_FLG(F) (regs8->f |= (F))
#define CLEAR_FLG(F) (regs8->f &= ~(F))

typedef struct registers8 {
  uint8_t f;
  uint8_t a;
  uint8_t c;
  uint8_t b;
  uint8_t e;
  uint8_t d;
  uint8_t l;
  uint8_t h;
  uint16_t sp;
  uint16_t pc;
} registers8;

typedef struct registers16 {
  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;
  uint16_t sp;
  uint16_t pc;
} registers16;

extern registers8 *regs8;
extern registers16 *regs16;

CASSERT(sizeof(registers16) == sizeof(registers8));

#endif /* !REGS_H */

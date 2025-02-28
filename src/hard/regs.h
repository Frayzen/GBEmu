#ifndef REGS_H
#define REGS_H

#include <stdint.h>

#define HIGH(Reg) ((Reg) & 0xF0)
#define LOW(Reg) ((Reg) & 0x0F)

#define FLAG_Z_MSK (1 << 1)
#define FLAG_N_MSK (1 << 2)
#define FLAG_H_MSK (1 << 3)
#define FLAG_C_MSK (1 << 4)

typedef struct registers {
  uint16_t af;
  uint16_t bc;
  uint16_t de;
  uint16_t hl;
  uint16_t sp;
  uint16_t pc;
} registers;

#endif /* !REGS_H */

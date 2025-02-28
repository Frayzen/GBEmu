#ifndef OPERAND_ACCESSOR_H
#define OPERAND_ACCESSOR_H

#include "hard/regs.h"
#include "utils.h"
#include <cstddef>
#include <stdlib.h>
#include <stdint.h>

uint8_t *r8_accessor(char val) {
  switch (val) {

  case 0:
    return &regs.b;
  case 1:
    return &regs.c;
  case 2:
    return &regs.d;
  case 3:
    return &regs.e;
  case 4:
    return &regs.h;
  case 5:
    return &regs.l;
  case 6:
    return &(*regs.h);
  case 7:
    return &regs.a;
  case 8:
    return &regs.a;
  default:
    printerr("Error while trying to access r8 register %d\n", val);
    return NULL;
  }
}

#endif /* !OPERAND_ACCESSOR_H */

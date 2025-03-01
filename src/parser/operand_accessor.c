#include "operand_accessor.h"
#include "hard/regs.h"
#include "parser/operand_list.h"
#include "ram/ram.h"
#include "ui/ui.h"
#include "utils.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// returns the pointer to the data pointed by the operand
uint8_t *r8_accessor(uint8_t val) {
  switch (val) {
  case 0:
    return &regs8->b;
  case 1:
    return &regs8->c;
  case 2:
    return &regs8->d;
  case 3:
    return &regs8->e;
  case 4:
    return &regs8->h;
  case 5:
    return &regs8->l;
  case 6:
    return get_ram_8ptr(regs16->hl);
  case 7:
    return &regs8->a;
  default:
    printerr("Error while trying to access r8 register %d\n", val);
    return NULL;
  }
}

#define R16_ACC_FLG_NONE 0
#define R16_ACC_FLG_STK 1
#define R16_ACC_FLG_MEM 2

// returns the pointer to the data pointed by the operand
uint16_t *r16_accessor(uint8_t val, int flags) {

  // TODO still need to handle hl+ and hl- (outside of this function)

  switch (val) {
  case 0:
    return &regs16->bc;
  case 1:
    return &regs16->de;
  case 2:
    return &regs16->hl;
  case 3: {
    if (flags == R16_ACC_FLG_STK)
      return &regs16->af;
    else if (flags == R16_ACC_FLG_MEM)
      return &regs16->hl;
    return &(regs16->sp);
  }
  default:
    printerr("Error while trying to access r16 register %d\n", val);
    return NULL;
  }
}

// returns the value of the condition associated
uint8_t cond_accessor(uint8_t val) {
  switch (val) {
  case 0:
    return !(regs8->f & FLAG_Z_MSK);
  case 1:
    return regs8->f & FLAG_Z_MSK;
  case 2:
    return !(regs8->f & FLAG_C_MSK);
  case 3:
    return regs8->f & FLAG_C_MSK;
  default:
    printerr("Error while trying to access cond register %d\n", val);
    exit(1);
    return 0;
  }
}

uint8_t *static_accessor(uint8_t val) {
  static uint8_t static_accessors[2] = {};
  static uint8_t last_static_index = 0;
  uint8_t *cur = static_accessors + last_static_index;
  last_static_index = (last_static_index + 1) % 2;
  *cur = val;
  return cur;
}

#define R16_ACC_FLG_NONE 0
#define R16_ACC_FLG_STK 1
#define R16_ACC_FLG_MEM 2
int get_r16_accessor_mask(operand_type type) {
  switch (type) {
  case r16:
  case sp:
  case hl:
    return R16_ACC_FLG_NONE;
  case r16stk:
    return R16_ACC_FLG_STK;
  case r16mem:
  case brak_r16mem:
    return R16_ACC_FLG_MEM;
  default:
    printerr("Error, weird operand for r16 ask : %d\n", type);
    exit(1);
  }
}

operand_value non_immediate_accessor(operand_type type, uint8_t hex, uint8_t mask) {
  union operand_value v;
  uint8_t offsethex = 0;
  if (mask != 0) {
    offsethex = hex;
    while (!(mask & 0b1)) {
      mask >>= 1;
      offsethex >>= 1;
    }
    offsethex &= mask;
  } else if (type == a)
    offsethex = 7; // value of a 8bits register
  else if (type == brak_c)
    offsethex = 1; // value of c 8bits register
  else if (type == hl)
    offsethex = 2; // value of hl 16bits register (without r16 flag)
  else if (type == sp)
    offsethex = 3; // value of sp 16bits register (without r16 flag)

  switch (type) {
  case a:
  case brak_c:
  case r8:
    return (operand_value)r8_accessor(offsethex);
  case sp:
  case hl:
  case r16:
  case r16stk:
  case r16mem:
  case brak_r16mem:
    return (operand_value)r16_accessor(offsethex, get_r16_accessor_mask(type));

  case b3:
    return (operand_value)static_accessor(offsethex);
  case tgt3:
    return (operand_value)static_accessor(offsethex * 8);
  case cond:
    return (operand_value)static_accessor(cond_accessor(offsethex));
  default:
    printerr("Error, weird operand involved : %d\n", type);
    exit(1);
  }
}

operand_value immediate_accessor(operand_type type) {
  uint8_t *address = ram + (regs8->pc++);
  switch (type) {
  case imm8:
    return (operand_value)address;
  case imm16:
    regs8->pc++;
    return (operand_value)address;
  case brak_imm16:
    regs8->pc++;
    return (operand_value)get_ram_16ptr(*((uint16_t *)address));
  case brak_imm8:
    return (operand_value)get_ram_8ptr(*address);
  case sp_plus_imm8:
  default:
    printerr("Error, weird immediate operand involved : %d\n", type);
    exit(1);
  }
}

operand_value operand_accessor(operand_type type, uint8_t hex, uint8_t msk) {
  if (type == no_oprd)
    return (operand_value)NULL;
  switch (type) {
  case imm8:
  case imm16:
  case brak_imm16:
  case brak_imm8:
  case sp_plus_imm8:
    return (operand_value)immediate_accessor(type);
  default:
    break;
  }
  // Non immediate fallback
  return non_immediate_accessor(type, hex, msk);
}

void operands_accessor(uint8_t cur_byte, operator* op, operand_value *first, operand_value *second) {

  *first = operand_accessor(op->op1_type, cur_byte, op->op1_mask);
  *second = operand_accessor(op->op2_type, cur_byte, op->op2_mask);
}

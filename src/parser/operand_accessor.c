#include "operand_accessor.h"
#include "hard/regs.h"
#include "parser/operand_list.h"
#include "ram/ram.h"
#include "utils.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// returns the pointer to the data pointed by the operand
operand r8_accessor(uint8_t val) {
  operand ret = {};
  ret.size = size8;
  switch (val) {
  case 0:
    ret.val = &regs8->b;
    break;
  case 1:
    ret.val = &regs8->c;
    break;
  case 2:
    ret.val = &regs8->d;
    break;
  case 3:
    ret.val = &regs8->e;
    break;
  case 4:
    ret.val = &regs8->h;
    break;
  case 5:
    ret.val = &regs8->l;
    break;
  case 6:
    ret.val = &regs16->hl;
    ret.deref = 1;
    break;
  case 7:
    ret.val = &regs8->a;
    break;
  default:
    printerr("Error while trying to access r8 register %d\n", val);
    break;
  }
  return ret;
}

#define R16_ACC_FLG_NONE 0
#define R16_ACC_FLG_STK 1
#define R16_ACC_FLG_MEM 2

// returns the pointer to the data pointed by the operand
operand r16_accessor(uint8_t val, int flags, int deref) {
  operand ret = {};
  ret.size = size16;
  ret.deref = deref;

  switch (val) {
  case 0:
    ret.val = &regs16->bc;
    break;
  case 1:
    ret.val = &regs16->de;
    break;
  case 2:
    ret.val = &regs16->hl;
    break;
  case 3: {
    if (flags == R16_ACC_FLG_STK)
      ret.val = &regs16->af;
    else if (flags == R16_ACC_FLG_MEM)
      ret.val = &regs16->hl;
    else
      ret.val = &regs16->sp;
    break;
  }
  default:
    printerr("Error while trying to access r16 register %d\n", val);
    break;
  }
  if (flags == R16_ACC_FLG_MEM)
  {
    ret.modify = (val == 3 ? -1 : (val == 2 ? 1 : 0));
  }
  return ret;
}

// returns the value of the condition associated
uint8_t cond_value(uint8_t val) {
  switch (val) {
  case 0:
    return !(regs8->f & Z_FLG);
  case 1:
    return regs8->f & Z_FLG;
  case 2:
    return !(regs8->f & C_FLG);
  case 3:
    return regs8->f & C_FLG;
  default:
    printerr("Error while trying to access cond register %d\n", val);
    exit(1);
    return 0;
  }
}

operand static_accessor(uint8_t val) {
  static uint8_t static_accessors[2] = {};
  static uint8_t last_static_index = 0;

  uint8_t *cur = static_accessors + last_static_index;
  last_static_index = (last_static_index + 1) % 2;

  operand ret = {
      .val = cur,
      .size = size8,
  };
  return ret;
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

operand non_immediate_accessor(operand_type type, uint8_t hex, uint8_t mask) {
  operand v;
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
    return r8_accessor(offsethex);
  case sp:
  case hl:
  case r16:
  case r16stk:
  case r16mem:
  case brak_r16mem:
    return r16_accessor(offsethex, get_r16_accessor_mask(type), type == brak_r16mem);
  case b3:
    return static_accessor(offsethex);
  case tgt3:
    return static_accessor(offsethex * 8);
  case cond:
    return static_accessor(cond_value(offsethex));
  default:
    printerr("Error, weird operand involved : %d\n", type);
    exit(1);
    break;
  }
}

operand immediate_accessor(operand_type type) {
  operand ret = {};
  ret.val = (ram + (regs8->pc++));
  switch (type) {
  case imm8:
    ret.size = size8;
    break;
  case imm16:
    regs8->pc++;
    ret.size = size16;
    break;
  case brak_imm16:
    regs8->pc++;
    ret.size = size16;
    ret.deref = 1;
    break;
  case brak_imm8:
    ret.size = size8;
    ret.deref = 1;
    break;
  case sp_plus_imm8: {
    ret.size = size16;
    void *val = NULL;
    val += regs16->sp + *(uint8_t *)ret.val;
    ret.val = val;
    break;
  }
  default:
    printerr("Error, weird immediate operand involved : %d\n", type);
    exit(1);
    break;
  }
  return ret;
}

operand operand_accessor(operand_type type, uint8_t hex, uint8_t msk) {
  if (type == no_oprd)
    return static_accessor(0);
  switch (type) {
  case imm8:
  case imm16:
  case brak_imm16:
  case brak_imm8:
  case sp_plus_imm8:
    return immediate_accessor(type);
  default:
    break;
  }
  // Non immediate fallback
  return non_immediate_accessor(type, hex, msk);
}

void operands_accessor(uint8_t cur_byte, operator* op, operand *first, operand *second) {
  *first = operand_accessor(op->op1_type, cur_byte, op->op1_mask);
  *second = operand_accessor(op->op2_type, cur_byte, op->op2_mask);
}

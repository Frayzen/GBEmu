#ifndef OPERATORS_LIST_H
#define OPERATORS_LIST_H

// See: https://gbdev.io/gb-opcodes/optables/#prefixed

#include "parser/operand_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#define MSK_NONE 0b00000000

#define MSK_54 0b00110000
#define MSK_43 0b00011000
#define MSK_543 0b00111000
#define MSK_210 0b00000111

// name
#define OPERATOR_LIST \
  X(nop)              \
  X(ld)               \
  X(inc)              \
  X(dec)              \
  X(add)              \
  X(rlca)             \
  X(rrca)             \
  X(rla)              \
  X(rra)              \
  X(daa)              \
  X(cpl)              \
  X(scf)              \
  X(ccf)              \
  X(jr)               \
  X(stop)             \
  X(halt)             \
  X(adc)              \
  X(sub)              \
  X(sbc)              \
  X(and)              \
  X(xor)              \
  X(or)               \
  X(cp)               \
  X(ret)              \
  X(reti)             \
  X(jp)               \
  X(call)             \
  X(rst)              \
  X(pop)              \
  X(push)             \
  X(ldh)              \
  X(di)               \
  X(ei)               \
  X(rlc)              \
  X(rrc)              \
  X(rl)               \
  X(rr)               \
  X(sla)              \
  X(sra)              \
  X(swap)             \
  X(srl)              \
  X(bit)              \
  X(res)              \
  X(set)

enum operator_type {
#define X(name, ...) name,
  OPERATOR_LIST
#undef X
};

// type (from enum), operand_type1, operand_type2, hexa, mask_oprd1, mask_oprd2, cbprefix
#define OPERATOR_DETAILS                                       \
  /* DONE */                                                   \
  X(nop, no_oprd, no_oprd, 0b00000000, MSK_NONE, MSK_NONE, 0)  \
  /* DONE */                                                   \
  X(ld, r16, brak_imm16, 0b00000001, MSK_54, MSK_NONE, 0)      \
  X(ld, brak_r16mem, a, 0b00000010, MSK_54, MSK_NONE, 0)       \
  X(ld, a, brak_r16mem, 0b00001010, MSK_NONE, MSK_54, 0)       \
  X(ld, brak_imm16, sp, 0b00001000, MSK_NONE, MSK_NONE, 0)     \
  /* DONE */                                                   \
  X(inc, r16, no_oprd, 0b00000011, MSK_54, MSK_NONE, 0)        \
  X(dec, r16, no_oprd, 0b00001011, MSK_54, MSK_NONE, 0)        \
  X(add, hl, r16, 0b00001001, MSK_NONE, MSK_54, 0)             \
  /* DONE */                                                   \
  X(inc, r8, no_oprd, 0b00000100, MSK_543, MSK_NONE, 0)        \
  X(dec, r8, no_oprd, 0b00000101, MSK_543, MSK_NONE, 0)        \
  /* DONE */                                                   \
  X(ld, r8, imm8, 0b00000110, MSK_543, MSK_NONE, 0)            \
  /* DONE */                                                   \
  X(rlca, no_oprd, no_oprd, 0b00000111, MSK_NONE, MSK_NONE, 0) \
  X(rrca, no_oprd, no_oprd, 0b00001111, MSK_NONE, MSK_NONE, 0) \
  X(rla, no_oprd, no_oprd, 0b00010111, MSK_NONE, MSK_NONE, 0)  \
  X(rra, no_oprd, no_oprd, 0b00011111, MSK_NONE, MSK_NONE, 0)  \
  X(daa, no_oprd, no_oprd, 0b00100111, MSK_NONE, MSK_NONE, 0)  \
  X(cpl, no_oprd, no_oprd, 0b00101111, MSK_NONE, MSK_NONE, 0)  \
  X(scf, no_oprd, no_oprd, 0b00110111, MSK_NONE, MSK_NONE, 0)  \
  X(ccf, no_oprd, no_oprd, 0b00111111, MSK_NONE, MSK_NONE, 0)  \
  /* DONE */                                                   \
  X(jr, imm8, no_oprd, 0b00011000, MSK_NONE, MSK_NONE, 0)      \
  X(jr, cond, imm8, 0b00100000, MSK_43, MSK_NONE, 0)           \
  /* DONE */                                                   \
  X(stop, no_oprd, no_oprd, 0b00010000, MSK_NONE, MSK_NONE, 0) \
  /* DONE */                                                   \
  X(ld, r8, r8, 0b01000000, MSK_543, MSK_210, 0)               \
  /* DONE */                                                   \
  X(halt, no_oprd, no_oprd, 0b01110110, MSK_NONE, MSK_NONE, 0) \
  /* DONE */                                                   \
  X(add, a, r8, 0b10000000, MSK_NONE, MSK_210, 0)              \
  X(adc, a, r8, 0b10001000, MSK_NONE, MSK_210, 0)              \
  X(sub, a, r8, 0b10010000, MSK_NONE, MSK_210, 0)              \
  X(sbc, a, r8, 0b10011000, MSK_NONE, MSK_210, 0)              \
  X(and, a, r8, 0b10100000, MSK_NONE, MSK_210, 0)              \
  X(xor, a, r8, 0b10101000, MSK_NONE, MSK_210, 0)              \
  X(or, a, r8, 0b10110000, MSK_NONE, MSK_210, 0)               \
  X(cp, a, r8, 0b10111000, MSK_NONE, MSK_210, 0)               \
  /* DONE */                                                   \
  X(add, a, imm8, 0b11000110, MSK_NONE, MSK_NONE, 0)           \
  X(adc, a, imm8, 0b11001110, MSK_NONE, MSK_NONE, 0)           \
  X(sub, a, imm8, 0b11010110, MSK_NONE, MSK_NONE, 0)           \
  X(sbc, a, imm8, 0b11011110, MSK_NONE, MSK_NONE, 0)           \
  X(and, a, imm8, 0b11100110, MSK_NONE, MSK_NONE, 0)           \
  X(xor, a, imm8, 0b11101110, MSK_NONE, MSK_NONE, 0)           \
  X(or, a, imm8, 0b11110110, MSK_NONE, MSK_NONE, 0)            \
  X(cp, a, imm8, 0b11111110, MSK_NONE, MSK_NONE, 0)            \
  /* DONE */                                                   \
  X(ret, cond, no_oprd, 0b11000000, MSK_43, MSK_NONE, 0)       \
  X(ret, no_oprd, no_oprd, 0b11001001, MSK_NONE, MSK_NONE, 0)  \
  X(reti, no_oprd, no_oprd, 0b11011001, MSK_NONE, MSK_NONE, 0) \
  X(jp, cond, imm16, 0b11000010, MSK_43, MSK_NONE, 0)          \
  X(jp, imm16, no_oprd, 0b11000011, MSK_NONE, MSK_NONE, 0)     \
  X(jp, hl, no_oprd, 0b11101001, MSK_NONE, MSK_NONE, 0)        \
  X(call, cond, imm16, 0b11000100, MSK_43, MSK_NONE, 0)        \
  X(call, imm16, no_oprd, 0b11001101, MSK_NONE, MSK_NONE, 0)   \
  X(rst, tgt3, no_oprd, 0b11000111, MSK_543, MSK_NONE, 0)      \
  /* DONE */                                                   \
  X(pop, r16stk, no_oprd, 0b11000001, MSK_54, MSK_NONE, 0)     \
  X(push, r16stk, no_oprd, 0b11000101, MSK_54, MSK_NONE, 0)    \
  /* DONE */                                                   \
  X(ldh, brak_c, a, 0b11100010, MSK_NONE, MSK_NONE, 0)         \
  X(ldh, brak_imm8, a, 0b11100000, MSK_NONE, MSK_NONE, 0)      \
  X(ld, brak_imm16, a, 0b11101010, MSK_NONE, MSK_NONE, 0)      \
  X(ldh, a, brak_c, 0b11110010, MSK_NONE, MSK_NONE, 0)         \
  X(ldh, a, brak_imm8, 0b11110000, MSK_NONE, MSK_NONE, 0)      \
  X(ld, a, brak_imm16, 0b11111010, MSK_NONE, MSK_NONE, 0)      \
  /* DONE */                                                   \
  X(add, sp, imm8, 0b11101000, MSK_NONE, MSK_NONE, 0)          \
  X(ld, hl, sp_plus_imm8, 0b11111000, MSK_NONE, MSK_NONE, 0)   \
  X(ld, sp, hl, 0b11101001, MSK_NONE, MSK_NONE, 0)             \
  /* DONE */                                                   \
  X(di, no_oprd, no_oprd, 0b11110011, MSK_NONE, MSK_NONE, 0)   \
  X(ei, no_oprd, no_oprd, 0b11111011, MSK_NONE, MSK_NONE, 0)   \
  /* CB PREFIX */                                              \
  /* DONE */                                                   \
  X(rlc, r8, no_oprd, 0b00000000, MSK_210, MSK_NONE, 1)        \
  X(rrc, r8, no_oprd, 0b00001000, MSK_210, MSK_NONE, 1)        \
  X(rl, r8, no_oprd, 0b00010000, MSK_210, MSK_NONE, 1)         \
  X(rr, r8, no_oprd, 0b00110000, MSK_210, MSK_NONE, 1)         \
  X(sla, r8, no_oprd, 0b00011000, MSK_210, MSK_NONE, 1)        \
  X(sra, r8, no_oprd, 0b00101000, MSK_210, MSK_NONE, 1)        \
  X(swap, r8, no_oprd, 0b00110000, MSK_210, MSK_NONE, 1)       \
  X(srl, r8, no_oprd, 0b00111000, MSK_210, MSK_NONE, 1)        \
  /* DONE */                                                   \
  X(bit, b3, r8, 0b01000000, MSK_543, MSK_210, 1)              \
  X(res, b3, r8, 0b10000000, MSK_543, MSK_210, 1)              \
  X(set, b3, r8, 0b11000000, MSK_543, MSK_210, 1)

typedef struct operator{
  enum operator_type type;
  uint8_t value;
  enum operand_type op1_type;
  enum operand_type op2_type;
  uint8_t op1_mask;
  uint8_t op2_mask;
  int cb_prefix;
}
operator;

operator operator_almanac[] = {
#define X(optype, op1, op2, hex, msk1, msk2, use_cb, ...) \
  {                                                       \
      .type = optype,                                     \
      .value = hex,                                       \
      .op1_type = op1,                                    \
      .op2_type = op2,                                    \
      .op1_mask = msk1,                                   \
      .op2_mask = msk2,                                   \
      .cb_prefix = use_cb,                                \
  },

    OPERATOR_DETAILS
#undef X
};

const int operator_amount = sizeof(operator_almanac) / sizeof(operator);

operator* get_op(uint8_t hex, int prev_cb) {
  for (int i = 0; i < operator_amount; i++) {
    operator* op = operator_almanac + i;
    if (op->cb_prefix != prev_cb)
      continue;
    uint8_t mask = ~op->op1_mask & ~op->op2_mask;
    if ((op->value ^ (hex & mask)) == 0) {
      return op;
    }
  }
  return NULL;
}

char *op_to_str(const operator* op) {
#define X(optype, op1, op2, hex, msk1, msk2, prev_cb...) \
  if (op->value == hex && op->cb_prefix == prev_cb)      \
    return #optype " " #op1 " " #op2;
  OPERATOR_DETAILS
#undef X
  return "Unkown op";
}

int operator_byte_consumption(const operator* op) {
  assert(op != NULL);
  return operand_byte_consumption(op->op1_type) + operand_byte_consumption(op->op2_type);
}

#endif /* !OPERATORS_LIST_H */

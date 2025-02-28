#ifndef OPERAND_LIST_H
#define OPERAND_LIST_H

#include "parser/operand_list.h"
#define MSK_NONE 0x11111111

#define MSK_54 0x00110000
#define MSK_43 0x00011000
#define MSK_543 0x00010000
#define MSK_210 0x00000111

#define OPERATOR_LIST                                       \
  /* DONE */                                                \
  X(nop, no_oprd, no_oprd, 0x00000000, MSK_NONE, MSK_NONE)  \
  /* DONE */                                                \
  X(ld, r16, brak_imm16, 0x00000001, MSK_54, MSK_NONE)      \
  X(ld, brak_r16mem, a, 0x00000010, MSK_54, MSK_NONE)       \
  X(ld, a, brak_r16mem, 0x00001010, MSK_NONE, MSK_54)       \
  X(ld, brak_imm16, sp, 0x00001000, MSK_NONE, MSK_NONE)     \
  /* DONE */                                                \
  X(inc, r16, no_oprd, 0x00000011, MSK_54, MSK_NONE)        \
  X(dec, r16, no_oprd, 0x00001011, MSK_54, MSK_NONE)        \
  X(add, hl, r16, 0x00001001, MSK_NONE, MSK_54)             \
  /* DONE */                                                \
  X(inc, r8, no_oprd, 0x00000100, MSK_543, MSK_NONE)        \
  X(dec, r8, no_oprd, 0x00000101, MSK_543, MSK_NONE)        \
  /* DONE */                                                \
  X(ld, r8, imm8, 0x00000110, MSK_543, MSK_NONE)            \
  /* DONE */                                                \
  X(rlca, no_oprd, no_oprd, 0x00000111, MSK_NONE, MSK_NONE) \
  X(rrca, no_oprd, no_oprd, 0x00001111, MSK_NONE, MSK_NONE) \
  X(rla, no_oprd, no_oprd, 0x00010111, MSK_NONE, MSK_NONE)  \
  X(rra, no_oprd, no_oprd, 0x00011111, MSK_NONE, MSK_NONE)  \
  X(daa, no_oprd, no_oprd, 0x00100111, MSK_NONE, MSK_NONE)  \
  X(cpl, no_oprd, no_oprd, 0x00101111, MSK_NONE, MSK_NONE)  \
  X(scf, no_oprd, no_oprd, 0x00110111, MSK_NONE, MSK_NONE)  \
  X(ccf, no_oprd, no_oprd, 0x00111111, MSK_NONE, MSK_NONE)  \
  /* DONE */                                                \
  X(jr, imm8, no_oprd, 0x00011000, MSK_NONE, MSK_NONE)      \
  X(jr, cond, imm8, 0x00100000, MSK_43, MSK_NONE)           \
  /* DONE */                                                \
  X(stop, no_oprd, no_oprd, 0x00010000, MSK_NONE, MSK_NONE) \
  /* DONE */                                                \
  X(ld, r8, r8, 0x01000000, MSK_543, MSK_210)               \
  /* DONE */                                                \
  X(halt, no_oprd, no_oprd, 0x01110110, MSK_NONE, MSK_NONE) \
  /* DONE */                                                \
  X(add, a, r8, 0x10000000, MSK_NONE, MSK_210)              \
  X(adc, a, r8, 0x10001000, MSK_NONE, MSK_210)              \
  X(sub, a, r8, 0x10010000, MSK_NONE, MSK_210)              \
  X(sbc, a, r8, 0x10011000, MSK_NONE, MSK_210)              \
  X(and, a, r8, 0x10100000, MSK_NONE, MSK_210)              \
  X(xor, a, r8, 0x10101000, MSK_NONE, MSK_210)              \
  X(or, a, r8, 0x10110000, MSK_NONE, MSK_210)               \
  X(cp, a, r8, 0x10111000, MSK_NONE, MSK_210)               \
  /* DONE */                                                \
  X(add, a, imm8, 0x11000110, MSK_NONE, MSK_NONE)           \
  X(adc, a, imm8, 0x11001110, MSK_NONE, MSK_NONE)           \
  X(sub, a, imm8, 0x11010110, MSK_NONE, MSK_NONE)           \
  X(sbc, a, imm8, 0x11011110, MSK_NONE, MSK_NONE)           \
  X(and, a, imm8, 0x11100110, MSK_NONE, MSK_NONE)           \
  X(xor, a, imm8, 0x11101110, MSK_NONE, MSK_NONE)           \
  X(or, a, imm8, 0x11110110, MSK_NONE, MSK_NONE)            \
  X(cp, a, imm8, 0x11111110, MSK_NONE, MSK_NONE)            \
  /* DONE */                                                \
  X(ret, cond, no_oprd, 0x11000000, MSK_43, MSK_NONE)       \
  X(ret, no_oprd, no_oprd, 0x11001001, MSK_NONE, MSK_NONE)  \
  X(reti, no_oprd, no_oprd, 0x11011001, MSK_NONE, MSK_NONE) \
  X(jp, cond, imm16, 0x11000010, MSK_43, MSK_NONE)          \
  X(jp, imm16, no_oprd, 0x11000011, MSK_NONE, MSK_NONE)     \
  X(jp, hl, no_oprd, 0x11101001, MSK_NONE, MSK_NONE)        \
  X(call, cond, imm16, 0x11000100, MSK_43, MSK_NONE)        \
  X(call, imm16, no_oprd, 0x11001101, MSK_NONE, MSK_NONE)   \
  X(rst, tgt3, no_oprd, 0x11000111, MSK_543, MSK_NONE)      \
  /* DONE */                                                \
  X(pop, r16stk, no_oprd, 0x11000001, MSK_54, MSK_NONE)     \
  X(push, r16stk, no_oprd, 0x11000101, MSK_54, MSK_NONE)    \
  /* DONE */                                                \
  X(ldh, brak_c, a, 0x11100010, MSK_NONE, MSK_NONE)         \
  X(ldh, brak_imm8, a, 0x11100000, MSK_NONE, MSK_NONE)      \
  X(ld, brak_imm16, a, 0x11101010, MSK_NONE, MSK_NONE)      \
  X(ldh, a, brak_c, 0x11110010, MSK_NONE, MSK_NONE)         \
  X(ldh, a, brak_imm8, 0x11110000, MSK_NONE, MSK_NONE)      \
  X(ld, a, brak_imm16, 0x11111010, MSK_NONE, MSK_NONE)      \
  /* DONE */                                                \
  X(add, sp, imm8, 0x11101000, MSK_NONE, MSK_NONE)          \
  X(ld, hl, sp_plus_imm8, 0x11111000, MSK_NONE, MSK_NONE)   \
  X(ld, sp, hl, 0x11101001, MSK_NONE, MSK_NONE)             \
  /* DONE */                                                \
  X(di, no_oprd, no_oprd, 0x11110011, MSK_NONE, MSK_NONE)   \
  X(ei, no_oprd, no_oprd, 0x11111011, MSK_NONE, MSK_NONE)

#define X(name, op1, op2, hex, msk1, msk2, ...) name##_##op1##_##op2,
enum operators {
  OPERATOR_LIST
};
#undef X

#endif /* !OPERAND_LIST_H */

#ifndef OPERAND_LIST_H
#define OPERAND_LIST_H

#define OPERAND_LIST \
  X(no_oprd)         \
  X(r8)              \
  X(r16)             \
  X(r16stk)          \
  X(r16mem)          \
  X(a)               \
  X(hl)              \
  X(b3)              \
  X(tgt3)            \
  X(imm8)            \
  X(imm16)           \
  X(brak_imm16)      \
  X(brak_imm8)       \
  X(brak_r16mem)     \
  X(sp_plus_imm8)

enum operands {
#define X(op, ...) op,
  OPERAND_LIST
#undef X
};

#endif /* !OPERAND_LIST_H */

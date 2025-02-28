#ifndef OPERAND_LIST_H
#define OPERAND_LIST_H

// name, byteConsumption, operand_accesor
#define OPERAND_LIST \
  X(no_oprd, 0)      \
  X(r8, 0)           \
  X(r16, 0)          \
  X(r16stk, 0)       \
  X(r16mem, 0)       \
  X(a, 0)            \
  X(hl, 0)           \
  X(b3, 0)           \
  X(tgt3, 0)         \
  X(imm8, 1)         \
  X(imm16, 2)        \
  X(brak_imm16, 2)   \
  X(brak_imm8, 1)    \
  X(brak_r16mem, 0)  \
  X(cond, 0)         \
  X(brak_c, 0)       \
  X(sp, 0)           \
  X(sp_plus_imm8, 1)

enum operand_type {
#define X(op, ...) op,
  OPERAND_LIST
#undef X
};

int operand_byte_consumption(enum operand_type op) {
  switch (op) {
#define X(op, amount, ...) \
  case op:                 \
    return amount;
    OPERAND_LIST
#undef X
  default:
    return 0;
  }
}



#endif /* !OPERAND_LIST_H */

#include "operand_list.h"

int operand_byte_consumption(operand_type op) {
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

int is_u16(operand_type op) {
  switch (op) {
  case r16:
  case r16stk:
  case r16mem:
  case hl:
  case imm16:
  case brak_imm16:
  case brak_r16mem:
  case sp:
  case sp_plus_imm8:
    return 1;
  default:
    return 0;
  }
}

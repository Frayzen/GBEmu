#include "operand_list.h"

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

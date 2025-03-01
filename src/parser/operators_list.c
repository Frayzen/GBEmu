#include "operators_list.h"

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

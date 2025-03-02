#ifndef OPERAND_ACCESSOR_H
#define OPERAND_ACCESSOR_H

#include "parser/operators_list.h"
#include <stdint.h>

typedef enum operand_size {
  size8,
  size16,
} operand_size;
typedef struct operand {
  void* val; // castable to uint16_t* according to size
  operand_size size;
  int deref;
  int modify;
} operand;

void operands_accessor(uint8_t cur_byte, operator* op, operand *first, operand *second);

#endif /* !OPERAND_ACCESSOR_H */

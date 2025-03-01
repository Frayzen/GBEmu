#ifndef OPERAND_ACCESSOR_H
#define OPERAND_ACCESSOR_H

#include "parser/operators_list.h"
#include <stdint.h>

typedef union operand_value {
  uint8_t* u8;
  uint16_t* u16;
  void* empty;
} operand_value;

void operands_accessor(operator* op, operand_value *first, operand_value *second);

#endif /* !OPERAND_ACCESSOR_H */

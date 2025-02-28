#ifndef OPERAND_ACCESSOR_H
#define OPERAND_ACCESSOR_H

#include "parser/operand_list.h"
#include <stdint.h>

typedef union operand_value {
  uint8_t u8;
  uint8_t* pu8;
  uint16_t* pu16;
} operand_value;

operand_value operand_accessor(operand_type type, uint8_t hex, uint8_t mask);

#endif /* !OPERAND_ACCESSOR_H */

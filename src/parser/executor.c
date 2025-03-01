#include "executor.h"
#include "parser/operand_list.h"

void execute_operator(operator* op, operand_value *v1, operand_value *v2) {
  switch (op->type) {
  case ld:
    if (is_u16(op->op1_type) && is_u16(op->op2_type))
      *v1->u16 = *v2->u16;
    break;
  case nop:
  case inc:
  case dec:
  case add:
  case rlca:
  case rrca:
  case rla:
  case rra:
  case daa:
  case cpl:
  case scf:
  case ccf:
  case jr:
  case stop:
  case halt:
  case adc:
  case sub:
  case sbc:
  case and:
  case xor:
  case or:
  case cp:
  case ret:
  case reti:
  case jp:
  case call:
  case rst:
  case pop:
  case push:
  case ldh:
  case di:
  case ei:
  case rlc:
  case rrc:
  case rl:
  case rr:
  case sla:
  case sra:
  case swap:
  case srl:
  case bit:
  case res:
  case set:
    break;
  }
}

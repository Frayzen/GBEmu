#include "executor.h"
#include "exec/exec_tools.h"
#include "hard/ime.h"
#include "hard/regs.h"
#include "parser/operand_accessor.h"
#include "parser/operand_list.h"
#include "ram/ram.h"
#include "utils.h"
#include <stdint.h>

void execute_operator(operator* op, operand *v1, operand *v2) {

  if (op->op1_type == cond) {
    if (!get_val(v1))
      return;
    v1 = v2;
    v2 = NULL;
  }

  uint16_t prev1 = get_val(v1);
  uint16_t prev2 = get_val_size(v2, v1->size);
  switch (op->type) {
  case ldh: // no flag affected
  case ld:
    assign(v1, v2);
    break;

  case nop: // no flag affected
    break;

  // SUM USAGE
  case inc:
    set_flag(prev1 == MAX_UINT8, CLEAR, prev1 == MAX_UINT4, IGNORE);
    sum(v1, 1); // handle flags
    break;
  case dec:
    sum(v1, -1); // handle flags
    break;
  case add:
    prev2 = get_val_size(v2, v1->size);
    sum(v1, prev2); // handle flags
    break;
  case adc:
    sum(v1, prev2 + GET_FLG(C_FLG)); // handle flags
    break;
  case sub:
    sum(v1, -prev2); // handle flags
    break;
  case sbc:
    sum(v1, -prev2 - GET_FLG(C_FLG)); // handle flags
    break;

  // ROTATES
  case rlc:
  case rlca:
    set_flag(CLEAR, CLEAR, CLEAR, rotate(v1, LEFT, !CICLE_C));
    break;
  case rrc:
  case rrca:
    set_flag(CLEAR, CLEAR, CLEAR, rotate(v1, RIGHT, !CICLE_C));
    break;
  case rl:
  case rla:
    set_flag(CLEAR, CLEAR, CLEAR, rotate(v1, LEFT, CICLE_C));
    break;
  case rr:
  case rra:
    set_flag(CLEAR, CLEAR, CLEAR, rotate(v1, RIGHT, CICLE_C));
    break;

  case cpl:
    assign_val(v1, ~prev1);
    set_flag(IGNORE, SET, SET, IGNORE);
    break;
  case scf:
    set_flag(IGNORE, CLEAR, CLEAR, SET);
    break;
  case ccf:
    set_flag(IGNORE, CLEAR, CLEAR, GET_FLG(C_FLG) == 0);
    break;

  // JUMPS, no flag affected
  case jr:
    regs8->pc += prev1;
    break;
  case jp:
    regs8->pc = prev1;
    break;
  case rst:
  case call:
    *get_ram_16ptr(--regs16->sp) = regs16->pc;
    regs8->pc = prev1;
    break;

  // TODOS
  case daa:
    // TODO
    break;
  case stop:
    // TODO
    break;
  case halt:
    // TODO
    break;

  // TESTING
  case and:
    assign_val(v1, prev1 & get_val(v2));
    set_flag(get_val(v1) == 0, CLEAR, SET, CLEAR);
    break;
  case xor:
    assign_val(v1, prev1 ^ get_val(v2));
    set_flag(get_val(v1) == 0, CLEAR, CLEAR, CLEAR);
    break;
  case or:
    assign_val(v1, prev1 | get_val(v2));
    set_flag(get_val(v1) == 0, CLEAR, CLEAR, CLEAR);
    break;
  case cp:
    set_sum_flag(v1, get_val(v2));
    break;

    // RETURN no flag affected
  case ret:
    regs16->pc = *get_ram_16ptr(regs16->sp++);
    break;
  case reti:
    regs16->pc = *get_ram_16ptr(regs16->sp++);
    ime = 1;
    break;

    // STACK
  case pop: // no flag affected otherwise
    assign_val(v1, *get_ram_16ptr(regs16->sp++));
    break;
  case push: // no flag affected
    *get_ram_16ptr(--regs16->sp) = get_val(v1);
    break;

  // INTERRUPTS
  case di:
    ime = 0;
    break;
  case ei:
    ime = 1;
    break;

  // SHIFTS
  case sla:
    shift8b(v1, LEFT, SFT_LOGIC); // update flag
    break;
  case sra:
    shift8b(v1, RIGHT, SFT_ARITHM); // update flag
    break;
  case srl:
    shift8b(v1, RIGHT, SFT_LOGIC); // update flag
    break;
  case swap:
    assign_val(v1, ((prev1 & 0x0F) << 4) + ((prev1 & 0xF0) >> 4));
    set_flag(prev1 == 0, CLEAR, CLEAR, CLEAR);
    break;

  // BIT SET
  case bit:
    set_flag((1 << prev1) & prev2, CLEAR, SET, IGNORE);
    break;
  case res: // no flag affected
    assign_val(v2, prev2 & ~(1 << prev1));
    break;
  case set: // no flag affected
    assign_val(v2, prev2 | (1 << prev1));
    break;
  }
}

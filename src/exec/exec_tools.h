#ifndef EXEC_TOOLS_H
#define EXEC_TOOLS_H

#include "parser/operand_accessor.h"

uint16_t get_val_size(const operand *op, operand_size size);
uint16_t get_val(const operand *op);
void assign(operand *dst, const operand *src);

// sign is either 1 or -1 for increment or decrement respectively
void assign_val(const operand *op, uint16_t v);
// modify dst and set the flags
void sum(operand *dst, uint16_t v);
// return result of operation, do not modify dst
uint16_t set_sum_flag(const operand *dst, uint16_t v);

#define CLEAR 0
#define SET 1
#define IGNORE -1
// -1 to clear, 1 to set, ignore otherwise
void set_flag(int z, int n, int h, int c);

#define LEFT 1
#define RIGHT -1

#define CICLE_C 1
// return carry value, steps is negative for right
int rotate(operand *op, int steps, int cicle_c);

#define SFT_LOGIC 0
#define SFT_ARITHM 1
// also update flag, dir is LEFT or RIGHT, behavior is SFT_LOGIC or SFT_ARITHM
void shift8b(operand *p, int dir, int behavior);

#endif /* !EXEC_TOOLS_H */

#include "exec_tools.h"
#include "hard/regs.h"
#include "parser/operand_accessor.h"
#include "ram/ram.h"
#include <stdint.h>

static void *get_ptr(const operand *op) {
  if (op->deref) {
    if (op->size == size8)
      return get_ram_8ptr(*(uint16_t *)op->val);
    else
      return get_ram_16ptr(*(uint16_t *)op->val);
  }
  return op->val;
}

uint16_t get_val_size(const operand *op, operand_size size) {
  void *ptr = get_ptr(op);
  if (op->size == size8)
    return *(uint8_t *)ptr;
  return *(uint16_t *)ptr;
}

uint16_t get_val(const operand *op) {
  return get_val_size(op, op->size);
}

void assign(operand *dst, const operand *src) {
  void *dstptr = get_ptr(dst);
  void *srcptr = get_ptr(src);
  if (dst->size == size8)
    *(uint8_t *)dstptr = *(uint8_t *)srcptr;
  else
    *(uint16_t *)dstptr = *(uint16_t *)srcptr;
}

// sign is either 1 or -1 for increment or decrement respectively
void assign_val(const operand *op, uint16_t v) {
  void *dstptr = get_ptr(op);
  if (op->size == size8)
    *(uint8_t *)op->val = v;
  else
    *(uint16_t *)op->val = v;
}

// return result of operation, do not modify dst
uint16_t set_sum_flag(const operand *dst, uint16_t v) {
  uint16_t dstv = get_val(dst);
  int sizelen = dst->size == size8 ? 8 : 16;
  uint16_t res = (dstv + v) & (dst->size == size8 ? 0xFF : 0xFFFF);
  int hflag, cflag, nflag;
  if (v > 0) {
    nflag = CLEAR;
    hflag = res & (1 << (sizelen - 5));
    cflag = res & (1 << (sizelen - 1));
  } else {
    nflag = SET;
    hflag = (dstv & 0b111) < (-v & 0b111);
    cflag = dstv < -v;
  }
  set_flag(res == 0, nflag, hflag, cflag);
  return res;
}

// handles flag
void sum(operand *dst, uint16_t v) {
  assign_val(dst, set_sum_flag(dst, v));
}

#define CLEAR 0
#define SET 1
#define IGNORE -1

// -1 to clear, 1 to set, ignore otherwise
void set_flag(int z, int n, int h, int c) {
#define SET_FLAG_FROM(ValCond, Flag) \
  if ((ValCond) == SET)              \
    SET_FLG(Flag);                   \
  else if ((ValCond) == CLEAR)       \
    CLEAR_FLG(Flag);
  SET_FLAG_FROM(z, Z_FLG);
  SET_FLAG_FROM(n, N_FLG);
  SET_FLAG_FROM(h, H_FLG);
  SET_FLAG_FROM(c, C_FLG);
}

// left rot, steps is always < 8, return carry
static uint8_t rotl8(operand *op, int steps, int cycle_c) {
  uint8_t v = get_val(op);
  uint8_t new_carry = v & (1 << (8 - steps));
  int add = cycle_c ? GET_FLG(C_FLG) : new_carry;
  assign_val(op, (v << steps) + cycle_c);
  return new_carry;
}

// left rot, steps is always < 8, return carry
static uint8_t rotl16(operand *op, int steps, int cycle_c) {
  uint16_t v = get_val(op);
  uint16_t new_carry = v & (1 << (16 - steps));
  int add = cycle_c ? GET_FLG(C_FLG) : new_carry;
  assign_val(op, (v << steps) + add);
  return new_carry;
}

// return carry value
int rotate(operand *op, int steps, int cycle_c) {
  if (steps < 0)              // right rotate
    steps = 8 - (-steps % 8); // equivalent to 8-steps left rotate
  else
    steps = steps % 8;
  if (op->size == size8)
    return rotl8(op, steps, cycle_c);
  return rotl16(op, steps, cycle_c);
}

void shift8b(operand *p, int dir, int behavior) {
  uint8_t v = get_val(p);
  int carry_bit = dir == LEFT ? 7 : 0;
  uint16_t new_carry = v & (1 << carry_bit);
  if (dir == RIGHT) {
    if (behavior == SFT_ARITHM) {
      // [(unchanged) b7] -> ... -> b0   -> C
      assign_val(p, (v >> 1) + (v & 0x80));
    } else {
      // 0 -> b7 -> ... -> b0   -> C
      assign_val(p, v >> 1);
    }
  } else {
    // always left arithmetic
    // C <-   b7 <- ... <- b0 <- 0
    assign_val(p, v << 1);
  }
  set_flag(get_val(p), CLEAR, CLEAR, new_carry);
}

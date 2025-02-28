#include "parser.h"
#include "hard/regs.h"
#include "parser/operators_list.h"
#include "ram/ram.h"
#include "ui/ui.h"
#include "utils.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int load_rom(const char *path) {
  static FILE *file = NULL;
  file = fopen(path, "r");
  if (file == NULL) {
    printerr("Could not open %s\n", path);
    return 1;
  }
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  rewind(file);
  if (fsize > RAM_SIZE) {
    printerr("The rom %s is too large to be open\n", path);
    return 1;
  }
  fread(ram, fsize, 1, file);
  fclose(file);
  return 0;
}

int parse() {
  operator* op = NULL;

  uint8_t byte = ram[regs16->pc++];
  static int prev_cb = 0;

  if (byte == 0xcb && !prev_cb) {
    prev_cb = 1;
    byte = ram[regs16->pc++];
  }
  uilog("Got %02x\n", byte);
  if (!(op = get_op(byte, prev_cb))) {
    uilog("Could not interpret %x\n", byte);
    return 1;
  }
  uilog("Interpreted as %s\n", op_to_str(op));
  prev_cb = 0;

  int byte_consumption = operator_byte_consumption(op);
  static uint8_t immediate_operands[4];
  for (int i = 0; i < byte_consumption; i++) {
    immediate_operands[i] = ram[regs16->pc++];
  }
  return 0;
}

#include "parser.h"
#include "parser/operators_list.h"
#include "utils.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

static FILE *rom;

static int curbyte = 0;
// return 0 on success, non 0 value otherwise
int next_byte(uint8_t *out) {
  curbyte++;
  assert(rom != NULL);
  int val = fgetc(rom);
  if (val == EOF)
    return -1;
  *out = val;
  return 0;
}

int parse(const char *path) {
  rom = fopen(path, "r");
  if (rom == NULL) {
    printerr("Could not open %s\n", path);
    return 1;
  }
  uint8_t byte;
  operator* op = NULL;

  int prev_cb = 0;
  while (!next_byte(&byte)) {
    static int counter = 0;
    if (byte == 0xcb && !prev_cb) {
      /* printf(" => Continue further\n"); */
      /* wait_for_input(); */
      prev_cb = 1;
      continue;
    }
    counter++;
    if (counter == 13)
      return 0;
    if (!(op = get_op(byte, prev_cb))) {
      printerr("Could not interpret %x\n", byte);
      return 1;
    }
    prev_cb = 0;

    printf("\n(instruction %d, byte %02x) %02x = ", counter, curbyte, byte);
    printBits(byte);
    printf(" %s\n", op_to_str(op));
    int byte_consumption = operator_byte_consumption(op);
    /* printf("SHOULD CONSUME%d\n", byte_consumption); */
    for (int i = 0; i < byte_consumption; i++) {
      if (next_byte(&byte)) {
        printerr("Needed byte but no more found\n");
        return 1;
      }
      /* printf("CONSUME %x\n", byte); */
    }
    /* wait_for_input(); */
  }

  fclose(rom);
  return 0;
}

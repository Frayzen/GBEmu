#include "parser.h"
#include "utils.h"
#include <stdio.h>

int parse(const char* path)
{
  FILE* rom = fopen(path, "r");
  if (rom == NULL)
  {
    printerr("Could not open this ROM");
    return 1;
  }
  fclose(rom);
  return 0;
}

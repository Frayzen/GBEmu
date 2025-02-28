#include "parser/parser.h"
#include "utils.h"
#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

int main(int argc, char *argv[]) {
  const char optstring[] = "";
  int res = 0;
  while ((res = getopt(argc, argv, optstring)) != -1) {
    if (res == '?') {
      return 1;
    }
    // optind contains the position of the value of the option
  }
  int first_arg = optind;

  if (argc - first_arg == 0)
  {
    printerr("Please provide a ROM\n");
    return 1;
  }
  return parse(argv[first_arg]);
}

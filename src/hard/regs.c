#include "regs.h"

registers8 regs;
registers8 *regs8 = &regs;
registers16 *regs16 = (registers16 *)&regs;
CASSERT(sizeof(registers16) == sizeof(registers8));
CASSERT(sizeof(registers16) == sizeof(registers8));
CASSERT(sizeof(registers16) == sizeof(registers8));
CASSERT(sizeof(registers16) == sizeof(registers8));

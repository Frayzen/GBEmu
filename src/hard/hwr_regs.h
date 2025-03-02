#ifndef HWR_REGS_H
#define HWR_REGS_H

#define W 1
#define R 2
#define R_W (W & R)

#define HARDWARE_REGISTER_LIST \
  X(TIMA, 0xFF04, R_W)         \
  X(TMA, 0xFF05, R_W)          \
  X(TIMA, 0xFF06, R_W)         \
  X(TAC, 0xFF07, R_W)         \
                               \
  X(LCDC, 0xFF40, R_W)         \
  X(STAT, 0xFF41, R_W)         \
  X(SCX, 0xFF42, R_W)          \
  X(SCY, 0xFF43, R_W)          \
  X(LY, 0xFF44, R_W)           \
  X(LYC, 0xFF45, R_W)          \
  X(BGP, 0xFF47, R_W)          \
  X(OBJP0, 0xFF48, R_W)        \
  X(OBJP1, 0xFF49, R_W)        \
  X(WY, 0xFF4A, R_W)           \
  X(WX, 0xFF4B, R_W)


#endif /* !HWR_REGS_H */

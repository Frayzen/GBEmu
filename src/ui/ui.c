#include "ui.h"
#include "hard/regs.h"
#include "utils.h"
#include <assert.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <time.h>

static WINDOW *mainwin, *regwin, *screenwin, *logwin, *logpad;
static int width, height = 0;

void create_win(WINDOW **win, int percent) {
  static int fromX = 0;
  assert(fromX < width);
  int w = percent * width / 100;
  if (win != NULL) {
    WINDOW *created = newwin(height, w, 0, fromX);
    wmove(created, 0, 0);
    *win = created;
  }
  fromX += w;
}

static void cleanup() {
  endwin();
}

void setup_ui() {
  mainwin = initscr();
  getmaxyx(mainwin, height, width);
  create_win(&regwin, PERCENT_REG);
  create_win(NULL, PERCENT_GAP);
  create_win(&screenwin, PERCENT_SCREEN);
  create_win(NULL, PERCENT_GAP);
  create_win(&logwin, PERCENT_LOG);

  int dx, dy;
  getmaxyx(logwin, dy, dx);
  logpad = newpad(10000, dx - 2);

  curs_set(0);
  noecho();

  atexit(cleanup);
  clear();
  display();
}

void uilog(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vw_printw(logpad, fmt, args);
  va_end(args);
}

void refresh_log() {
  box(logwin, '|', '-');
  mvwprintw(logwin, 0, 1, "[LOG]");
  wrefresh(logwin);
  int x, y, dx, dy, curx, cury;
  getbegyx(logwin, y, x);
  getmaxyx(logwin, dy, dx);
  getyx(logpad, cury, curx);
  cury = MAX(0, cury - height + 2);
  prefresh(logpad, cury, 0, y + 1, x + 1, y + dy - 2, x + dx - 2);
}

void refresh_reg() {
  box(regwin, '|', '-');
  mvwprintw(regwin, 0, 1, "[REG]");
  mvwprintw(regwin,1,1, "AF: %02x", regs16->af);
  mvwprintw(regwin,2,1, "BC: %02x", regs16->bc);
  mvwprintw(regwin,3,1, "DE: %02x", regs16->de);
  mvwprintw(regwin,4,1, "HL: %02x", regs16->hl);
  mvwprintw(regwin,5,1, "SP: %02x", regs16->sp);
  mvwprintw(regwin,6,1, "PC: %02x", regs16->pc);
  wrefresh(regwin);
}

void display() {
  refresh();
  refresh_log();
  refresh_reg();
  wrefresh(screenwin);
}

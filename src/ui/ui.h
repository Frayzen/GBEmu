#ifndef UI_H
#define UI_H


/* WINDOW LAYOUT
 * _____________________
 * |## __________ @@@@@|
 * |## |        | @@@@@|
 * |## |  MAIN  | @@@@@|
 * |## | SCREEN | @@@@@|
 * |## |________| @@@@@|
 * |##            @@@@@|
 * |___________________|
 *
 * #: logs
 * @: registers
 */

#include "utils.h"
#define PERCENT_REG 10
#define PERCENT_LOG 30
#define PERCENT_GAP 5

#define PERCENT_SCREEN 100 - (PERCENT_REG + PERCENT_LOG + 2 * PERCENT_GAP)
CASSERT(PERCENT_SCREEN < 100 && PERCENT_SCREEN > 30)

void setup_ui();
void uilog(const char *fmt, ...);

void display();

#endif /* !UI_H */

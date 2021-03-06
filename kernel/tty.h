#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stdbool.h>

#define TTY_COLOR(FG, BG) ((BG << 4) | (FG & 0x0F))

void tty_init(void);

uint16_t tty_getwidth(void);
uint16_t tty_getheight(void);

uint8_t tty_getcolor(void);
void tty_setcolor(uint8_t);

uint16_t tty_getcursorx(void);
uint16_t tty_getcursory(void);
void tty_setcursorx(uint16_t);
void tty_setcursory(uint16_t);
bool tty_getcursorvis(void);
void tty_setcursorvis(bool);

void tty_clear(void);
void tty_clearline(void);

void tty_putchar(unsigned char);
void tty_puts(char*);

#endif

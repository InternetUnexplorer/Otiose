#include "../../tty.h"
#include "../../color.h"
#include "platform.h"

static uint16_t *vga_memory = (uint16_t*) 0xB8000;

static uint8_t color = TTY_COLOR(LIGHTGRAY, BLACK);
static uint16_t cursor_x, cursor_y;

static inline uint16_t *_charaddr(uint16_t, uint16_t);
static inline void _updatecursor(void);
static inline void _clear(void);
static inline void _clearline(void);
static inline void _newline(void);
static inline void _setchar(unsigned char);
static inline void _putchar(unsigned char);
static inline void _puts(char*);

inline uint16_t tty_getwidth() {
    return 80;
}

inline uint16_t tty_getheight() {
    return 25;
}

inline uint8_t tty_getcolor() {
    return color;
}

inline void tty_setcolor(uint8_t c) {
    color = c;
}

inline uint16_t tty_getcursorx() {
    return cursor_x;
}

inline uint16_t tty_getcursory() {
    return cursor_y;
}

inline void tty_setcursorx(uint16_t x) {
    cursor_x = x;
}

inline void tty_setcursory(uint16_t y) {
    cursor_y = y;
}


static inline uint16_t *_charaddr(uint16_t x, uint16_t y) {
    return vga_memory + y * tty_getwidth() + x;
}

static inline void _updatecursor() {
    // Credit: https://wiki.osdev.org/Text_Mode_Cursor
    uint16_t offset = cursor_y * tty_getwidth() + cursor_x;
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (offset & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((offset >> 8) & 0xFF));
}


static inline void _clear(void) {
    for (cursor_y = 0; cursor_y < tty_getheight(); cursor_y++)
        _clearline();
    cursor_y = 0;
}

inline void tty_clear(void) {
    _clear();
    _updatecursor();
}

static inline void _clearline() {
    for (cursor_x = 0; cursor_x < tty_getwidth(); cursor_x++)
        _setchar(' ');
    cursor_x = 0;
}

inline void tty_clearline() {
    _clearline();
    _updatecursor();
}

static inline void _newline() {
    if (++cursor_y == tty_getheight()) {
        for (cursor_y = 0; cursor_y < tty_getheight() - 1; cursor_y++)
            for (cursor_x = 0; cursor_x < tty_getwidth(); cursor_x++)
                *_charaddr(cursor_x, cursor_y) = *_charaddr(cursor_x, cursor_y + 1);
        _clearline();
    }
    cursor_x = 0;
}

inline void tty_newline() {
    _newline();
    _updatecursor();
}

static inline void _setchar(unsigned char c) {
    *_charaddr(cursor_x, cursor_y) = c | color << 8;
}

static inline void _putchar(unsigned char c) {
    _setchar(c);
    if (++cursor_x > tty_getwidth())
        _newline();
}

inline void tty_putchar(unsigned char c) {
    _putchar(c);
    _updatecursor();
}

static inline void _puts(char* s) {
    while (*s)
        _putchar(*s++);
}

inline void tty_puts(char* s) {
    _puts(s);
    _updatecursor();
}

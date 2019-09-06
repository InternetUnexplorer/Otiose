#include "../../tty.h"
#include "../../color.h"
#include "platform.h"

static uint16_t *vga_memory = (uint16_t*) 0xB8000;

static uint8_t color = TTY_COLOR(LIGHTGRAY, BLACK);
static uint16_t cursor_x, cursor_y;
static bool cursor_visible = true;

static inline uint16_t *_charaddr(uint16_t, uint16_t);
static inline void _updatecursorpos(void);
static inline void _updatecursorvis(void);
static inline void _clear(void);
static inline void _clearline(void);
static inline void _newline(void);
static inline void _tab(void);
static inline void _backspace(void);
static inline void _verticaltab(void);
static inline void _setchar(unsigned char);
static inline void _putchar(unsigned char);
static inline void _puts(char*);

inline void tty_init() {
    _clear();
    _updatecursorpos();
    _updatecursorvis();
}

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
    _updatecursorpos();
}

inline void tty_setcursory(uint16_t y) {
    cursor_y = y;
    _updatecursorpos();
}

inline bool tty_getcursorvis() {
    return cursor_visible;
}

inline void tty_setcursorvis(bool v) {
    cursor_visible = v;
    _updatecursorvis();
}

static inline uint16_t *_charaddr(uint16_t x, uint16_t y) {
    return vga_memory + y * tty_getwidth() + x;
}

static inline void _updatecursorpos() {
    // Credit: https://wiki.osdev.org/Text_Mode_Cursor
    uint16_t offset = cursor_y * tty_getwidth() + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (offset & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((offset >> 8) & 0xFF));
}

static inline void _updatecursorvis() {
    // Credit: https://wiki.osdev.org/Text_Mode_Cursor
    if (cursor_visible) {
        outb(0x3D4, 0x0A);
        outb(0x3D5, (inb(0x3D5) & 0xC0) | 0xE);
        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xE0) | 0xF);
    } else {
        outb(0x3D4, 0x0A);
        outb(0x3D5, 0x20);
    }
}

static inline void _clear(void) {
    for (cursor_y = 0; cursor_y < tty_getheight(); cursor_y++)
        _clearline();
    cursor_y = 0;
}

inline void tty_clear(void) {
    _clear();
    _updatecursorpos();
}

static inline void _clearline() {
    for (cursor_x = 0; cursor_x < tty_getwidth(); cursor_x++)
        _setchar(' ');
    cursor_x = 0;
}

inline void tty_clearline() {
    _clearline();
    _updatecursorpos();
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

static inline void _tab() {
    do {
        _putchar(' ');
    } while(cursor_x % 8);
}

static inline void _backspace() {
    if (cursor_x)
        cursor_x--;
    _setchar(' ');
}

static inline void _verticaltab() {
    uint16_t current_x = cursor_x;
    _newline();
    cursor_x = current_x;
}

static inline void _setchar(unsigned char c) {
    *_charaddr(cursor_x, cursor_y) = c | color << 8;
}

static inline void _putchar(unsigned char c) {
    switch (c) {
    case '\a': /* TODO */      break;
    case '\b': _backspace();   break;
    case '\n': _newline();     break;
    case '\r': cursor_x = 0;   break;
    case '\t': _tab();         break;
    case '\f': _verticaltab(); break;
    case '\v': _verticaltab(); break;
    default:
        _setchar(c);
        if (++cursor_x == tty_getwidth())
            _newline();
    }
}

inline void tty_putchar(unsigned char c) {
    _putchar(c);
    _updatecursorpos();
}

static inline void _puts(char* s) {
    while (*s)
        _putchar(*s++);
}

inline void tty_puts(char* s) {
    _puts(s);
    _updatecursorpos();
}

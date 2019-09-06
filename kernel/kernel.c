#include "tty.h"

void kernel_main(void) {
    tty_init();
    tty_puts("Hello, world!");
}

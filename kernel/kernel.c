#include "tty.h"

void kernel_main(void) {
	tty_clear();
	tty_puts("Hello, world!");
}

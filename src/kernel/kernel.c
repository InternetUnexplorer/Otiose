#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main(void) {
	uint16_t* terminal_buffer = (uint16_t*) 0xB8000;
	terminal_buffer[0] = 2 << 8 | 'H';
}

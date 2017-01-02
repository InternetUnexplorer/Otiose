#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kernel_main(void) {
	uint16_t* terminal_buffer = (uint16_t*) 0xB8000;
	char testStr[] = "Hello, world!";
	size_t i;
	for(i = 0; i < 13; i++)
		terminal_buffer[i] = 2 << 8 | testStr[i];
}

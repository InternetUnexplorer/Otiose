#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

void outb(uint16_t, uint8_t);
uint8_t inb(uint16_t);

#endif

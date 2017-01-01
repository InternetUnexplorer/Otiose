SYSROOT        ?= $(shell pwd)

HOST           ?= i686-elf
HOST_ARCH      ?= i386

AR             := $(HOST)-ar
AS             := $(HOST)-as
CC             := $(HOST)-gcc

PREFIX         := /usr
INCLUDE_DIR    := $(PREFIX)/include

CC_FLAGS       := --sysroot=$(SYSROOT) -O2 -g
LD_FLAGS       :=

export

ifneq (,$(findstring -elf,$(HOST))) # -elf gcc targets don't have a system include directory.
	CC_FLAGS   := -isystem=$(INCLUDE_DIR) $(CC_FLAGS)
endif

.PHONY: qemu kernel

qemu: kernel
	qemu-system-i386 -curses -kernel kernel/otiose.kernel

kernel:
	(cd kernel; make)

clean:
	(cd kernel; make clean)

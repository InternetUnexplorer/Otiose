include $(shell pwd)/make.config

.PHONY: qemu kernel

qemu: kernel
	qemu-system-i386 -curses -kernel kernel/otiose.kernel

kernel:
	(cd kernel; make)

clean:
	(cd kernel; make clean)

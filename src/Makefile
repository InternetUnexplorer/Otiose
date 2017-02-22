include $(shell pwd)/make.config

.PHONY: qemu

qemu: kernel/otiose.kernel
	qemu-system-i386 -curses -kernel kernel/otiose.kernel

kernel/otiose.kernel:
	(cd kernel; make otiose.kernel)

clean:
	(cd kernel; make clean)

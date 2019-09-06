include make.config

.PHONY: qemu-curses qemu-gtk kernel clean

qemu-curses: kernel
	qemu-system-$(HOST_ARCH) -display curses -kernel kernel/otiose.kernel

qemu-gtk: kernel
	qemu-system-$(HOST_ARCH) -display gtk -kernel kernel/otiose.kernel

kernel:
	(cd kernel; make otiose.kernel)

clean:
	(cd kernel; make clean)

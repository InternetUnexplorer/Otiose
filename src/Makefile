include make.config

.PHONY: qemu kernel clean

qemu: kernel
	qemu-system-i386 -kernel kernel/otiose.kernel

kernel:
	(cd kernel; make otiose.kernel)

clean:
	(cd kernel; make clean)

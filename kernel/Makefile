include ../make.config

CC_FLAGS       := $(CC_FLAGS) -ffreestanding -Wall -Wextra
LD_FLAGS       := $(LD_FLAGS)
LIBS           := $(LIBS) -nostdlib -flto

ARCH_DIR       := arch/$(HOST_ARCH)

include $(ARCH_DIR)/make.config
CC_FLAGS       := $(CC_FLAGS) $(KERNEL_ARCH_CC_FLAGS)
LD_FLAGS       := $(LD_FLAGS) $(KERNEL_ARCH_LD_FLAGS)
LIBS           := $(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel.o \

OBJS=\
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

LINK_LIST=\
$(LD_FLAGS) \
$(ARCH_DIR)/crti.o \
$(ARCH_DIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCH_DIR)/crtend.o \
$(ARCH_DIR)/crtn.o \

.PHONY: clean

.SUFFIXES: .o .c .S

otiose.kernel: $(OBJS) $(ARCH_DIR)/linker.ld
	$(strip $(CC) -T $(ARCH_DIR)/linker.ld -o otiose.kernel $(CC_FLAGS) $(LINK_LIST) )

$(ARCH_DIR)/crtbegin.o $(ARCH_DIR)/crtend.o:
	$(strip OBJ=`$(CC) $(CC_FLAGS) $(LD_FLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@ )

.c.o:
	$(strip $(CC) -MD -c $< -o $@ $(CC_FLAGS) )

.S.o:
	$(strip $(CC) -MD -c $< -o $@ $(CC_FLAGS) )

clean:
	rm -f otiose.kernel
	rm -f $(OBJS) *.o */*.o */*/*.d
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

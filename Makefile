BINARY     := pashahod_chdev
KERNEL      := /lib/modules/$(shell uname -r)/build
C_FLAGS     := -Wall
KMOD_DIR    := $(shell pwd)
TARGET_PATH := /lib/modules/$(shell uname -r)/kernel/drivers/char

OBJECTS := main.o

ccflags-y += $(C_FLAGS)

obj-m += $(BINARY).o

$(BINARY)-y := $(OBJECTS)

$(BINARY).ko:
    make -C $(KERNEL) M=$(KMOD_DIR) modules

install:
    cp $(BINARY).ko $(TARGET_PATH)
    depmod -a

uninstall:
    rm $(TARGET_PATH)/$(BINARY).ko
    depmod -a

clean:
    make -C $(KERNEL) M=$(KMOD_DIR) clean

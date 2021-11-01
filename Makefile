DRVNAME := pashahod_chdev
PWDDIR  := $(shell pwd)
SRC_DIRS :=src/
BUILD_DIR := build/
INC_DIR := include/
KERN_DIR := /lib/modules/$(shell uname -r)/build

MNAME   := $(DRVNAME).ko
SRCS := $(addprefix src/, pashahod_chdev.c)
OBJS := $(SRCS:.c=.o)

$(DRVNAME)-y := $(OBJS)

obj-$(CONFIG_PASHAHOD_CHDEV)+=$(DRVNAME).o

.PHONY: build clean
all: build
build:
	@echo "Build ${DRVNAME} driver"
	@echo "OBJS $(OBJS)"
	$(MAKE) -C $(KERN_DIR) M=$(PWDDIR) modules

clean:
	@echo "Clean $(DRVNAME)"
	@find . \( -name '*.o' -o -name '*.ko' -o -name '*.mod.c' -o -name '*.cmd' -o -name '*.markers' -o \
		-name '*.symvers' -o -name '*.builtin' -o -name '*.order' -o -name '*.o.d' -o -name 'version.h' \) -type f -delete





ifeq ($(KERNELRELEASE),)
	KERNEL_DIR ?= /usr/src/linux-headers-$(shell uname -r)
default:
	make -C $(KERNEL_DIR) modules M=$(shell pwd)
else
	obj-m := char_sample.o
endif

.PHONY: clean

clean:
	rm *.o *.ko modules.* Module.* *.mod.*

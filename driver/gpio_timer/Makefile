ifeq ($(KERNELRELEASE),)
	KERNEL_DIR ?= /opt/mpbox/targets/current/rootfs/usr/src/linux-2.6.36-mini6410/
default:
	make ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- -C $(KERNEL_DIR) modules M=$(shell pwd)
else
	obj-m := gpio_led.o
endif

.PHONY: clean install

clean:
	rm *.o *.ko modules.* Module.* *.mod.*

install:
	cp gpio_led.ko /opt/mpbox/targets/current/rootfs/root

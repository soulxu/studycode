
ifneq ($(KERNELRELEASE),)
	obj-m := usb_sample.o
else
	KERNELDIR ?= /usr/src/linux-headers-2.6.31-14-386/
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY: clean

clean:
	rm *.o *.mod.* *.ko

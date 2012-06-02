ifneq ($(KERNELRELEASE),)
	obj-m += iodev.o
	EXTRA_CFLAGS += -O
else
	KERNELDIR ?= /usr/src/linux-headers-$(shell uname -r)
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif
.PHONY: clean

clean:
	rm mcdev.ko *.o

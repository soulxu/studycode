ifneq ($(KERNELRELEASE),)
	obj-m += mcdev.o
	CFLAGS += -O -DMCDEV_DEBUG
else
	KERNELDIR ?= /usr/src/linux-2.6.16.27-2
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif
.PHONY: clean

clean:
	rm mcdev.ko *.o

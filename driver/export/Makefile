ifeq ($(KERNELRELEASE),)
	KERNELDIR := /usr/src/linux-headers-$(shell uname -r)
	PWD := $(shell pwd)
default:
	make -C $(KERNELDIR) modules M=$(PWD)
else
	obj-m := export.o
endif

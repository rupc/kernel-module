obj-m = clone.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep clone | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod clone
endif
	sudo insmod clone.ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


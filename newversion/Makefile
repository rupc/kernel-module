obj-m = newversion.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep newversion | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod newversion
endif
	sudo insmod newversion.ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


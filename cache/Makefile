obj-m = hello_cache.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep hello_cache | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod hello_cache
endif
	sudo insmod hello_cache.ko
	dmesg

rm :
	sudo rmmod hello_cache
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


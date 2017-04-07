obj-m = hello_mmap.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

ALREADY_INSTERTTED=$(shell lsmod | grep hello_mmap | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),hello_mmap)
	sudo rmmod hello_mmap
endif
	sudo insmod hello_mmap.ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


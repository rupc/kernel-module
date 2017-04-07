obj-m = hello_page.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep hello_page | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod hello_page
endif
	sudo insmod hello_page.ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


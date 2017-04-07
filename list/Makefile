module_name = list_practice
obj-m = list_practice.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
	sudo rmmod $(module_name)
	sudo insmod $(module_name).ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


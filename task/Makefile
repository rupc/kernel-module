obj-m = hello_task.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep hello_task | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod hello_task
endif
	sudo insmod hello_task.ko
	dmesg

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


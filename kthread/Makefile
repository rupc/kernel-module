obj-m = kthread.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep kthread | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod kthread
endif
	sudo insmod kthread.ko
	dmesg

rm :
	sudo rmmod kthread

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


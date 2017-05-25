obj-m = jiffies.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep jiffies | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod jiffies
endif
	sudo insmod jiffies.ko
	dmesg

rm :
	sudo rmmod jiffies
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


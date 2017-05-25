obj-m = hrtimer.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep hrtimer | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod hrtimer
endif
	sudo insmod hrtimer.ko
	dmesg

rm :
	sudo rmmod hrtimer
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


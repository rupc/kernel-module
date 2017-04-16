obj-m = kthread_changing_state2.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
ALREADY_INSTERTTED=$(shell lsmod | grep kthread_changing_state | awk '{print $1;}')

default :
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

run :
ifneq ($(ALREADY_INSTERTTED),)
	sudo rmmod kthread_changing_state
endif
	sudo insmod kthread_changing_state.ko
	dmesg

rm :
	sudo rmmod kthread_changing_state
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


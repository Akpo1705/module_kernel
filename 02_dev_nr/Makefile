obj-m += dev_nr.o
PREFIX = arm-linux-gnueabihf-
linux = /home/alex/test/rasspbery_pi2/kernel/5.10/linux

all:
	make ARCH=arm CROSS_COMPILE=$(PREFIX) -C $(linux) M=$(PWD) modules
	# make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make ARCH=arm CROSS_COMPILE=$(PREFIX) -C $(linux) M=$(PWD) clean
	# make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
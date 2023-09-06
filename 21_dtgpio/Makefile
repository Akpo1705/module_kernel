obj-m += dtgpio.o
PREFIX = arm-linux-gnueabihf-
linux = /home/alex/test/rasspbery_pi2/kernel/5.10/linux

all:
	make ARCH=arm CROSS_COMPILE=$(PREFIX) -C $(linux) M=$(PWD) modules
	# make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make ARCH=arm CROSS_COMPILE=$(PREFIX) -C $(linux) M=$(PWD) clean
	# make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


# 	/{
#         compatible = "brcm,bcm2835";
#         my_device {
#                 compatible = "brightlight,mydev";
#                 status = "okay";
#                 label = "Test";
#                 my_value = <12>;
#         };
# };

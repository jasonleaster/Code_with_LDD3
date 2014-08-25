# Code wrire 	: EOF
# code date 	: 2014.08.19
# e-mail	: jasonleaster@gmail.com
#
# THis Makefile is a demo only for ARM-architecture
#

ifneq ($(KERNELRELEASE),)

	obj-m := led_by_EOF.o

else
	CROSS_COMPILE = /usr/local/arm/4.3.2/bin/arm-linux-gcc/
	CC = CROSS_COMPILE	
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD	:=$(shell pwd)
	SUBDIR  := /Jason_with_ARM/linux-3.0.1/

modules:
	$(MAKE) -C $(SUBDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.order *.symvers *.ko *.mod*
endif

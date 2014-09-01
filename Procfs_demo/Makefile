# Code wrire 	: EOF
# code date 	: 2014.09.01
# e-mail	: jasonleaster@gmail.com
#
# THis Makefile is a demo only for x86-architecture
#

ifneq ($(KERNELRELEASE),)

	obj-m := proc_demo.o

else
	SUBDIR  := /lib/modules/$(shell uname -r)/build
	PWD	:=$(shell pwd)

modules:
	$(MAKE) -C $(SUBDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.order *.symvers *.ko *.mod*
endif

obj-m := hello.o
hello-objs := util.o

KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD)  

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

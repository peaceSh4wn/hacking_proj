obj-m := ps.o
ps-objs := hello.o util.o

KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD)  

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

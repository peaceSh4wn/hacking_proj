obj-m := ps.o
ps-objs := main.o util.o hook_fn.o

KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD)  

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

obj-m += hello1.o hello2.o

ccflags-y := -I$(src)/inc
ccflags-y += -g

KDIR ?= /home/vboxuser/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	cp hello1.ko hello1.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

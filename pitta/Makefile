TRUE = 1
gt = $(shell if [ $1 -gt $2 ] ; then echo $(TRUE); fi)
lt = $(shell if [ $1 -lt $2 ] ; then echo $(TRUE); fi)
eq = $(shell if [ $1 -eq $2 ] ; then echo $(TRUE); fi)

obj-m := pitta.o

ifneq ($(KERNELRELEASE),)

obj-m += $(if $(call eq, $(VERSION), 3), \
			$(if $(call eq, $(PATCHLEVEL), 7), \
					$(if $(call eq, $(SUBLEVEL), 10), test.o)))
else


PWD := $(shell pwd)
KDIR := /usr/src/linux

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
endif
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

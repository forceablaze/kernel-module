TRUE = 1
gt = $(shell if [ $1 -gt $2 ] ; then echo $(TRUE); fi)
lt = $(shell if [ $1 -lt $2 ] ; then echo $(TRUE); fi)
eq = $(shell if [ $1 -eq $2 ] ; then echo $(TRUE); fi)

LD = ld
PWD := $(shell pwd)
KDIR := /usr/src/linux

CXXOBJS := hello.o cpp_interface.o
PREBUILD_OBJ = prebuild.o
CXXSRC = $(CXXOBJS:.o=.cpp)

obj-m := cpp_mod.o
cpp_mod-objs := $(PREBUILD_OBJ) test.o kernel_api.o


default:
	$(MAKE) prebuild
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

prebuild: $(CXXOBJS)
	$(LD) -r -o $(PREBUILD_OBJ) $^

%.o: %.cpp
	$(CC) -c -o $@ -fno-builtin -fno-exceptions -fno-rtti -nostdinc $<

#endif

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean


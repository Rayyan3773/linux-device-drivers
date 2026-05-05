obj-m:= chardriver.o
kerndir:= /usr/src/linux-headers-$(shell uname -r)
pwd:= $(shell pwd)
all:
	make -C $(kerndir) M=$(pwd) modules

clean:
	make -C $(kerndir) M=$(pwd) clean

obj-m:=numdev.o
obj-m:=devnum2.o
obj-m:=devnum3.o
obj-m:=devnum4.o
obj-m:=filedev.o
obj-m:=filedev2.o
obj-m:=chardev.o
obj-m:=fileopr.o

kerndir:= /usr/src/linux-headers-$(shell uname -r)
pwd:= $(shell pwd)

all:
	make -C $(kerndir) M=$(pwd) modules

clean:
	make -C $(kerndir) M=$(pwd) clean

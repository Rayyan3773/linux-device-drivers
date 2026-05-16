obj-m:= driver.o

kerdir:= /usr/src/linux-headers-$(shell uname -r)
pwd:= $(shell pwd)

all:
	make -C $(kerdir) M=$(pwd) modules

clean:
	make -C $(kerdir) M=$(pwd) clean


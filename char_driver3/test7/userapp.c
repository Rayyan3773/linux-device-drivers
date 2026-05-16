#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mystruct.h"

#define DEVICE_FILE "/dev/mystruct"

int main(){
	int fd;
	int retval;
	abc user_struct = {5, 'a'};

	printf("opening file: %s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if(fd<0){
		perror("open failed");
		exit(1);
	}

	getchar();

	retval= write(fd, &user_struct, sizeof(user_struct));
	printf("write retval: %d\n", retval);
	getchar();

	user_struct.i=4;
	user_struct.c='b';

	retval = read(fd,&user_struct, sizeof(user_struct));
	printf("read retval: %d \t int:%d \t char: %c\n", retval, user_struct.i, user_struct.c);
	getchar();

	printf("closing file\n");
	close(fd);
	getchar();

	return 0;
}


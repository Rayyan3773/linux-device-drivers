#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE_FILE "/dev/msg"

int main(){
	int fd;
	int retval;
	char buffer[10];
	int i;

	printf("opening file: %s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if(fd<0){
		perror("open failed\n");
		exit(1);
	}

	getchar();

	retval = write(fd, "hello", 5);
	printf("write retval: %d\n", retval);
	getchar();

	retval = write(fd, "world", 5);
	printf("write retval: %d\n", retval);
	getchar();

	printf("closing file\n");
	close(fd);
	getchar();

	return 0;
}


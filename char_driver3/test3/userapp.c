#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mychardev"

int main(){
	int fd;
	int retval; 
	char buffer[10];

	printf("opening file: %s\n", DEVICE_FILE);
	fd=open(DEVICE_FILE, O_RDWR);
	if(fd<0){
		perror("open failed");
		exit(1);
	}

	getchar();

	retval = write(fd, "hello", 5);
	printf("write retval: %d\n", retval);
	getchar();

	retval = read(fd, buffer, 10);
	printf("read retval: %d\n", retval);
	getchar();

	printf("closing file\n");
	close(fd);
	getchar();

	return 0;
}

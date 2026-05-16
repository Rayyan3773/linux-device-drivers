#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_FILE "/dev/mystruct"

int main(){
	int fd;
	int retval;
	char* buffer = malloc(sizeof(char)*10); //allocating 10 bytes on the heap

	printf("opening file:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if(fd<0){
		perror("open failed");
		exit(1);
	}

	getchar();

	strcpy(buffer, "hello"); //copying hello into the buffer

	retval = write(fd, buffer, strlen(buffer));
	printf("write retval:%d\n", retval);
	getchar();
	
	printf("closing file\n");
	close(fd);
	getchar();

	return(0);
}


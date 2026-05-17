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
	
	for(i=0; i<250; i++){
		retval = write(fd, "hello",5);
		printf("write retval: %d\n", retval);
		if(retval !=5)
			break;
	}



	printf("closing file\n");
	close(fd);
	getchar();

	return 0;
}



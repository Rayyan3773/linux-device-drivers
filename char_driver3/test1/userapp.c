#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mychardev"

int main(){
	int fd;
	int retval;
	char buffer[10];
	pid_t pid;

	printf("opening file: %s\n", DEVICE_FILE);
	fd=open(DEVICE_FILE, O_RDWR);

	if(fd<0){
		perror("open failed");
		exit(1);
	}

	getchar();
	pid=fork();
	if(pid==0){
		printf("child process: executing and writing hello world: %ld\n", write(fd, "hello world", sizeof("hello world")));
	}
	else{
		printf("parent process: executing and writing hello embedded: %ld\n", write(fd, "hello embedded", sizeof("hello embedded")));
	}
	printf("closing file\n");
	close(fd);
	getchar();

	return 0;
}

	

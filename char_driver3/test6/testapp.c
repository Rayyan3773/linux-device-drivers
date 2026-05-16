#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int fd;
	unsigned long long old_jiffies;
	unsigned long long new_jiffies;

	fd=open("/dev/jiffies", O_RDWR);
	if(fd<0){
		perror("open failed");
		exit(2);
	}
	if (read(fd, &old_jiffies, sizeof(old_jiffies)) != sizeof(old_jiffies)){
	printf("failed in reafing first jiffies\n");
	exit(3);
	}
	else{
		printf("first read: %lld\n", old_jiffies);
	}
	sleep(2);
	if (read(fd, &new_jiffies, sizeof(new_jiffies)) != sizeof(new_jiffies)){
	printf("failed in reafing second jiffies\n");
	exit(4);
	}
	else{
		printf("second read: %lld\n", new_jiffies);
	}
	printf("difference: %lld\n", (new_jiffies - old_jiffies));
	close(fd);
}

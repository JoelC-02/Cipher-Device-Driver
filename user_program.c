#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main() {
        int fd = open("/dev/cipher",O_RDWR), opt;
        char buf[100];
        while(1) {
		printf(" 1: Cipher\n 2: Decipher\n 3: Quit\n Enter option: ");
		scanf("%d", &opt);
		if(opt == 3) break;
		memset(buf, 0, 256);
		printf("Enter data: ");
		scanf("%s", buf);
		write(fd, buf, strlen(buf));
		ioctl(fd, opt-1);
		read(fd,buf,sizeof(100));
		printf("Data: %s\n", buf);
	}
        close(fd);
        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <poll.h>
#include <signal.h>

int stop;

void sig_handler(){
        stop = 1;
}

int main(){

        int fd;
        int test;

        stop = 0;

        fd = open("/dev/irq_poll",O_RDONLY);

        if(fd < 0){
                perror("Could not open device file");
                return -1;
        }

        signal(SIGILL, sig_handler);

        printf("Wait for signal...\n");
        while(!stop){
                struct pollfd my_poll;
                memset(&my_poll,0,sizeof(my_poll));
                my_poll.fd = fd;
                my_poll.events = POLLIN;
                if(poll(&my_poll,1, 100) > 0){
                        if(my_poll.revents && POLLIN)
                                printf("Button was pressed!!!\n");
                }
        }


        return 0;
}
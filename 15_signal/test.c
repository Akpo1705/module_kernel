#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SIGTX 44
#define REGISTER_UAPP _IO('R', 'g')

void signalhandler(int sig){
        printf("Button was pressed!\n");
}

int main(int argc, char* argv[]){
        int fd;
        signal(SIGTX,signalhandler);

        printf("PID: %d\n", getpid());
        
        fd = open("/dev/irq_signal", O_RDONLY);
        if(fd < 0)
        {
                perror("Couldnt not open device file");
                return -1;
        }

        if( ioctl(fd,REGISTER_UAPP,NULL)){
                perror("Error registering app");
                close(fd);
                return -1;
        }

        printf("Wait for signal...\n");
        while(1){
                sleep(1);
        }

        return 0;


        printf("Hello world!!!\n");

        return 0;
}
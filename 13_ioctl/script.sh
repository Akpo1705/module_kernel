#!/bin/sh

NAME=ioctl
FOLDER=13_ioctl

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}
sshpass -pP@ssw0rd scp ./ioctl_test.h root@192.168.1.167:/home/${FOLDER}
arm-linux-gnueabihf-gcc test.c -o test || exit
sshpass -pP@ssw0rd scp ./test root@192.168.1.167:/home/${FOLDER}
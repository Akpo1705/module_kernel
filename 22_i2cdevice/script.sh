#!/bin/sh

NAME=i2cdevice
FOLDER=22_i2cdevice

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}
# arm-linux-gnueabihf-gcc test.c -o test || exit
# sshpass -pP@ssw0rd scp ./test root@192.168.1.167:/home/${FOLDER}
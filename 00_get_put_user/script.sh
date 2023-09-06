#!/bin/sh

NAME=gpu
FOLDER=00_gpu

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}

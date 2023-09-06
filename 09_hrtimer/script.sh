#!/bin/sh

NAME=hrtimer
FOLDER=09_hrtimer

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}
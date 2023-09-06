#!/bin/sh

NAME=params
FOLDER=12_params

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}
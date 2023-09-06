#!/bin/sh

NAME=gpio_irq
FOLDER=11_gpio_irq

sshpass -pP@ssw0rd scp ./${NAME}.ko root@192.168.1.167:/home/${FOLDER}
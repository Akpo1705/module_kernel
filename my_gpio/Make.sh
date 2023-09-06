#!/bin/sh 


make || exit
sshpass -pP@ssw0rd scp my_gpio.ko root@192.168.1.167:/home/my_gpio
#!/bin/sh

NAME=my_gpio

echo "====================================================="
rmmod ${NAME}
echo "-------------"
insmod ${NAME}.ko
dmesg | tail -n 10 || exit
echo "-------------"
head -n 1 /dev/${NAME} || exit
echo "-------------"
dmesg | tail -n 20
echo "-------------"
echo 0 > /dev/${NAME} || exit
echo "-------------"
dmesg | tail -n 20
echo "-------------"
echo 1 > /dev/${NAME}
echo "-------------"
dmesg | tail -n 20
echo "====================================================="
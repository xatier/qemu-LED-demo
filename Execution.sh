#!/bin/bash

make
exitVal=$?
if [ $exitVal != "0" ] 
then
	exit 1
fi

cd ../../Qemu/src

echo "#QEMU#"
./arm-softmmu/qemu-system-arm \
	-M stm32l152rbt6 \
	-nographic \
	-chardev socket,id=led_green,port=4242,host=localhost,nodelay \
	-chardev socket,id=led_blue,port=4243,host=localhost,nodelay \
	-chardev socket,id=user0,port=4244,host=localhost,nodelay \
	-kernel ../../Demonstrations/Demo1\ -\ LEDs/main_qemu.bin
exit 0

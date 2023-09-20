#!/bin/bash
input=$1

if [ $input == "update" ];then

    #binary update
#    sshpass -p 'rt2023' rsync -avz /home/user/build-uvcCameraOperation-RPi4_roadtech-Debug/uvcCameraOperation -e ssh root@10.42.0.91:/home/rt/uvcCameraOperation/bin
#    sshpass -p 'rt2023' rsync -avz /home/user/build-uvcCameraOperation-RPi4_roadtech-Debug/uvcCameraOperation -e ssh root@10.42.0.70:/home/rt/uvcCameraOperation/bin
#    sshpass -p 'rt2023' rsync -avz /home/user/build-uvcCameraOperation-RPi4_roadtech-Debug/uvcCameraOperation -e ssh root@10.42.0.83:/home/rt/uvcCameraOperation/bin
#    sshpass -p 'rt2023' rsync -avz /home/user/build-uvcCameraOperation-RPi4_roadtech-Debug/uvcCameraOperation -e ssh root@10.42.0.30:/home/rt/uvcCameraOperation/bin
#    sshpass -p 'rt2023' rsync -avz /home/user/build-uvcCameraOperation-RPi4_roadtech-Debug/uvcCameraOperation -e ssh root@10.42.0.220:/home/rt/uvcCameraOperation/bin

    sshpass -p 'rt2023' rsync -avz  /home/user/build-uvcCameraOperation-Qt5_15_7_rpi-Release/uvcCameraOperation -e ssh root@10.42.0.91:/home/rt/uvcCameraOperation/bin
    sshpass -p 'rt2023' rsync -avz  /home/user/build-uvcCameraOperation-Qt5_15_7_rpi-Release/uvcCameraOperation -e ssh root@10.42.0.70:/home/rt/uvcCameraOperation/bin
    sshpass -p 'rt2023' rsync -avz  /home/user/build-uvcCameraOperation-Qt5_15_7_rpi-Release/uvcCameraOperation -e ssh root@10.42.0.83:/home/rt/uvcCameraOperation/bin
    sshpass -p 'rt2023' rsync -avz  /home/user/build-uvcCameraOperation-Qt5_15_7_rpi-Release/uvcCameraOperation -e ssh root@10.42.0.30:/home/rt/uvcCameraOperation/bin
    sshpass -p 'rt2023' rsync -avz  /home/user/build-uvcCameraOperation-Qt5_15_7_rpi-Release/uvcCameraOperation -e ssh root@10.42.0.220:/home/rt/uvcCameraOperation/bin

fi

if [ $input == "auto_start_enable" ];then

    #program auto start enable
    sshpass -p 'rt2023' ssh rt@10.42.0.91 'sudo systemctl enable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.70 'sudo systemctl enable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.83 'sudo systemctl enable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.30 'sudo systemctl enable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.220 'sudo systemctl enable uvcCamera.service;sudo reboot'

fi

if [ $input == "auto_start_disable" ];then

    #program auto start disable
    sshpass -p 'rt2023' ssh rt@10.42.0.91 'sudo systemctl disable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.70 'sudo systemctl disable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.83 'sudo systemctl disable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.30 'sudo systemctl disable uvcCamera.service;sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.220 'sudo systemctl disable uvcCamera.service;sudo reboot'

fi

if [ $input == "poweroff" ];then

    #program system poweroff
    sshpass -p 'rt2023' ssh rt@10.42.0.91 'sudo poweroff'
    sshpass -p 'rt2023' ssh rt@10.42.0.70 'sudo poweroff'
    sshpass -p 'rt2023' ssh rt@10.42.0.83 'sudo poweroff'
    sshpass -p 'rt2023' ssh rt@10.42.0.30 'sudo poweroff'
    sshpass -p 'rt2023' ssh rt@10.42.0.220 'sudo poweroff'

fi

if [ $input == "reboot" ];then

    #program system reboot
    sshpass -p 'rt2023' ssh rt@10.42.0.91 'sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.70 'sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.83 'sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.30 'sudo reboot'
    sshpass -p 'rt2023' ssh rt@10.42.0.220 'sudo reboot'
fi

if [ $input == "mqttip2" ];then

    sshpass -p "rt2023" ssh rt@10.42.0.91 'echo "#10.42.0.69#usb-camera-ch1#60001" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.70 'echo "#10.42.0.69#usb-camera-ch2#60002" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.83 'echo "#10.42.0.69#usb-camera-ch3#60003" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.30 'echo "#10.42.0.69#usb-camera-ch4#60004" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.220 'echo "#10.42.0.69#usb-camera-ch5#60005" > /home/rt/config.txt'

fi

if [ $input == "mqttip1" ];then

    sshpass -p "rt2023" ssh rt@10.42.0.91 'echo "#10.42.0.41#usb-camera-ch1#60001" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.70 'echo "#10.42.0.41#usb-camera-ch2#60002" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.83 'echo "#10.42.0.41#usb-camera-ch3#60003" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.30 'echo "#10.42.0.41#usb-camera-ch4#60004" > /home/rt/config.txt'
    sshpass -p "rt2023" ssh rt@10.42.0.220 'echo "#10.42.0.41#usb-camera-ch5#60005" > /home/rt/config.txt'

fi

exit 0

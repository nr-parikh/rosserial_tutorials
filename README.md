# Testing repository for *rosserial* package

This repository contains the codes which are used for testing the communication between ROS and a Arduino development board and TeensyLC board. While all the programs can be used off the shelf for arduino, one must need to tweak *ArduinoHardware.h* file inorder to be able to communicate with ROS. All the code related which should be uploaded on the Arduino or Teensy can be found in the folder *microcontroller_code*.

## Setting up the Arduino IDE 

Assuming that ROS is already installed on the computer, installing the IDE for Arduino is the next step. It can be downloaded from official Arduino [site](https://www.arduino.cc/en/Main/OldSoftwareReleases#previous). Please note that the link provided here is to versions 1.8.2 or older since the Teensyduino version at this time does not support Arduino IDE version 1.8.3. In order to install the IDE, navigate to the downloaded folder from terminal and run `tar -xvzf arduino-1.x.x.tar.gz` where x varies depending on the version. This will unzip the file. Go to the newly created folder *arduino-1.x.x* and run `sudo ./install.sh`. 

## Installing *rosserial_arduino* package

This package is responsible to handle all the communication between Arduino and ROS. The advantage of using this package over any other serial library is that it allows the user to make Arduino a node in ROS network. This gives Arduino the capability to publish and subscribe to topics which are there in the network without any hassle. As mentioned on the official [page](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup), there are two different ways to install this package:

  1. Install from binaries. Run the following commands in the terminal in order to install the package.
      * `sudo apt-get install ros-<distro>-rosserial-arduino`
      * `sudo apt0get install ros-<distro>-rosserial`
  2. In case the method mentioned above doesn't work, the package can be built from source as follows.
      * `cd <workspace/src>`
      * `git clone https://github.com/ros-drivers/rosserial.git`
      * `cd ..`
      * `catkin_make`

For the first method please run `sudo apt-get update` before proceeding to install the package. 

## ROS library for Arduino 

To use the *rosserial* package with Arduino, this is the crucial step. This step will builf ROS library for Arduino. The location where the library is to be built is very important. It can be found in the *home* directory on the Linux system. Run the command `rosrun rosserial_arduino make_libraries.py <path to Arduino's libraries folder>`. After this step, ensure that *File->examples* shows *ros_lib*.

## Installing Teensyduino

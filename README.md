# *rosserial* Tutorials

This repository contains the codes which are used for testing the communication between ROS and a Arduino development board and TeensyLC board. While all the programs can be used off the shelf for arduino, one must need to tweak *ArduinoHardware.h* file inorder to be able to communicate with ROS. All the code related which should be uploaded on the Arduino or Teensy can be found in the folder *microcontroller_code*.

## Setting up the Arduino IDE 

Assuming that ROS is already installed on the computer, installing the IDE for Arduino is the next step. It can be downloaded from official Arduino [site](https://www.arduino.cc/en/Main/OldSoftwareReleases#previous). Please note that the link provided here is to versions 1.8.2 or older since the Teensyduino version at this time does not support Arduino IDE version 1.8.3. In order to install the IDE, navigate to the downloaded folder from terminal and run `tar -xvzf arduino-1.x.x.tar.gz` where x varies depending on the version. This will unzip the file. Go to the newly created folder *arduino-1.x.x* and run `sudo ./install.sh`. 

## Installing *rosserial_arduino* package

This package is responsible to handle all the communication between Arduino and ROS. The advantage of using this package over any other serial library is that it allows the user to make Arduino a node in ROS network. This gives Arduino the capability to publish and subscribe to topics which are there in the network without any hassle. As mentioned on the official [page](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup), there are two different ways to install this package:

  1. Install from binaries. Run the following commands in the terminal in order to install the package.
      * `sudo apt-get install ros-<distro>-rosserial-arduino`
      * `sudo apt-get install ros-<distro>-rosserial`
  2. In case the method mentioned above doesn't work, the package can be built from source as follows.
      * `cd <workspace/src>`
      * `git clone https://github.com/ros-drivers/rosserial.git`
      * `cd ..`
      * `catkin_make`

For the first method please run `sudo apt-get update` before proceeding to install the package. 

## ROS library for Arduino 

To use the *rosserial* package with Arduino, this is the crucial step. This step will builf ROS library for Arduino. The location where the library is to be built is very important. It can be found in the *home* directory on the Linux system. Run the command `rosrun rosserial_arduino make_libraries.py <path to Arduino's libraries folder>`. After this step, ensure that *File->examples* shows *ros_lib*.

## Installing Teensyduino

Teensyduino is an Arduino IDE plugin for Teensy boards. It can be downloaded from [here](https://www.pjrc.com/teensy/td_download.html). Once Arduino IDE is setup, run the Teensyduino installer to install the plugin. If using Linux environment, there might be a need to make the file executable, this can be done using the command: `chmod +x <TeensyduinoInstall>`. Then run the installer using `./TeensyduinoInstall.linux<xx>`.


## Notes for Teensy boards

On Linux environment, udev rule file needs to be copied to `/etc/udev/rules.d`. The file can be in the repository inside *misc_files* folder, [here](https://github.com/nr-parikh/rosserial_testing/blob/master/misc_files/49-teensy.rules). To copy this file to the aforementioned location run the command `sudo cp ~/home/rosserial_testing/misc_files/49-teensy.rules /etc/udev/rules.d/`. This file gives non-root users the permission to access Teensy board.

While the library for Arduino boards works off the shelf, there is minor modification in the file *ArduinoHardware.h* which needs to be done in order to be able to compile the Arduino code for Teensy boards. The file can be found in the *misc_files* folder of this repository. Replace the file generated in the folder *ros_lib* created earlier while building the ROS libraries for Arduino IDE with the one provided in the repository for Teensy boards.

## Running the code

All the codes in this repository, have been tested on both Arduino Uno and TeensyLC board. The repository contains following examples:

  * **Hello World!**
    * Multiple publishers on the Arduino node with subscribers on the node running on workstation. This program toggles the LED on in the callback fucntion.
      * Arduino example: multiple_pub.ino
      * ROS node: ros_arduino_multiple_pub_sub
    
  * **Servo Control** 
    * This is a very simple example which can be used to control a servo motor using ROS and Arduino. The example is same as it is available on the official site with additional publisher on the Arduino and corresponding subscriber on workstation.
      * Arduino example: servo_with_sub.ino
      * ROS node: ros_arduino_servo_with_sub
  
  * **PWM control of DC motor with standard message**
    * For Pulse Width Modulation, the motor driver being used becomes very important. Here, MD10C R3 motor driver has been used. Depending on the motor driver being used, the information needed to drive the motor changes and so does the information to be published from ROS. In this example, unsigned integers are being published to control the motor.
      * Arduino example: pwm_with_pub.ino
      * ROS node: ros_arduino_pwm_with_sub
  
  * **PWM control of DC motor with custom message**
    * In this example, the motor is being controlled again by MD10C driver but in Sign Magnitude mode. This mode requires two different variables and thus a custome message has been defined which carries all the information needed.
      * Arduino example: pwm_custom_message_pub.ino
      * ROS node: ros_arduino_pwm_custom_message
      * NOTE: When using custom messages after building the package, one needs to build Arduino libraries again in order to be able include the message type on Arduino.
        
  * **Hello World! with interrupts**
    * This is another simple example which also considers interrupts in the loop.
      * Arduino example: interrupt_with_blink_pub.ino
      * ROS node: ros_arduino_interrupt_blink
  
  * **PWM and servo control**
    * This example extends the previously defined examples and combines them to control two motors simultaneously. PWM in this example is being done using a custom message as mentioned above.
      * Arduino example: pwm_servo_pub.ino
      * ROS node: ros_arduino_pwm_servo
    
To run the code, please follow the instructions given below:
  * `cd ~/home/<workspace>/src`
  * `git clone https://github.com/nr-parikh/rosserial_tutorials.git`
  * `cd ..`
  * `catkin_make`
  * `sudo rm -rf <path to Arduino libraries>/ros_lib`
  * `rosrun rosserial_arduino make_libraries.py <path to Arduino libraries>`
  * Connect Arduino Uno board to your computer and upload an example
  * `roscore` 
  * `rosrun rosserial_python serial_node.py _port:=<device> _baud:=<baud rate>`
  * `rosrun ros_arduino_trial <example node>`
  
If the communication is not proper then the permission needs to be changed for the USB device. This can be done using `sudo chmod 666 <device>`.

/*
This program is used for testing the control of a DC motor by publishing PWM values on a -
topic at the same time listening to the string coming from arduino board. This has been tested with 
Arduino Uno board and Teensy LC board.

The motor-driver used for testing of this program is MD10C R3 by Cytron technologies. There are two 
operating mode in for this motor-driver. This program assumes that the physical connections
are done for Sign Magnitude mode. To be able to use this mode, a custom message is needed which
can carry both the direction of rotation as well as the speed of motion. The advantage of
using this mode is that we can control the velocity with better precision.  

Please take a note of how motor driver being used works and publish the message accordingly. 
*/


#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/String.h"
#include "ros_arduino_trial/pwm_signal.h"
#include <unistd.h>

#include <sstream>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "pwm_node");

  ros::NodeHandle n;

  ros::Publisher pwmPub = n.advertise<ros_arduino_trial::pwm_signal>("pwm_signal", 1000);
  ros::Subscriber sub = n.subscribe("listener", 1000, chatterCallback);

  ros::Rate loop_rate(5);

  ros_arduino_trial::pwm_signal signal;
  signal.dir = 0;
  signal.data = 0;

  // NOTE: The value of PWM signal to be published depends on the motor-driver one is using.

  for (int i=1; i<=10; i++){
    if (i>5) signal.data = 1;
    pwmPub.publish(signal);
    ros::spinOnce();
    loop_rate.sleep();
    signal.data = signal.data + 20;
    ROS_INFO("%d", i);
  }

  signal.dir = 0;
  signal.data = 0;
  pwmPub.publish(signal);

  ROS_INFO("PWM testing completed.");


  return 0;
}
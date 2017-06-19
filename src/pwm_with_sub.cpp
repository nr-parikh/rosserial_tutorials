/*
This program is used for testing the control of a DC motor by publishing PWM values on a -
topic at the same time listening to the string coming from arduino board. This has been tested with 
Arduino Uno board and Teensy LC board.

The motor-driver used for testing of this program is MD10C R3 by Cytron technologies. There are two 
operating mode in for this motor-driver. This program assumes that the physical connections
are done for Locked Antiphase motor control. This mode allows to use the standard messages available 
in ROS to control rather than creating custom ones. 

Please take a note of how motor driver being used works and publish the message accordingly. 
*/


#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/String.h"
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

  ros::Publisher pwmPub = n.advertise<std_msgs::UInt16>("pwm_signal", 1000);
  ros::Subscriber sub = n.subscribe("listener", 1000, chatterCallback);

  ros::Rate loop_rate(5);

  std_msgs::UInt16 signal;
  signal.data = 0;

  // NOTE: The value of PWM signal to be published depends on the motor-driver one is using.

  for (int i=1; i<=10; i++){
    pwmPub.publish(signal);
    ros::spinOnce();
    loop_rate.sleep();
    signal.data = signal.data + 20;
  }

  signal.data = 127;
  pwmPub.publish(signal);

  ROS_INFO("PWM testing completed.");


  return 0;
}
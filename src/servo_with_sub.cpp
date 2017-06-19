/*
This program is used for testing the control of servo by publishing the angle between 0-180 degrees on a -
topic at the same time listening to the string coming from arduino board. This has been tested with Arduino-
Uno board and Teensy LC board.
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

  ros::init(argc, argv, "servo_node");

  ros::NodeHandle n;

  ros::Publisher servoPub = n.advertise<std_msgs::UInt16>("servo_angle", 1000);
  ros::Subscriber sub = n.subscribe("listener", 1000, chatterCallback);

  ros::Rate loop_rate(10);

  std_msgs::UInt16 angle;
  angle.data = 0;

  // NOTE: Angle can be between 0 and 180 only. No other value is permitted. 

  for (int i=1; i<=18; i++){
    servoPub.publish(angle);
    ros::spinOnce();
    loop_rate.sleep();
    angle.data = angle.data + 10;
    ROS_INFO("%d",angle.data);
  }

  angle.data = 0;
  servoPub.publish(angle);
  ros::spinOnce();
  loop_rate.sleep();

  ROS_INFO("Servo testing completed.");


  return 0;
}
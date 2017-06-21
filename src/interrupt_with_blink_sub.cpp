/*
This program simply shows how to use multpiple subscribers and publshers to communicate with
Arduino board. This has been tested with Arduino Uno board and Teensy LC board. This only 
assembles simple examples provided on the official site into one.
*/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

#include <sstream>
#include <string>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  static std::string str = "I am RoCo!";
  ROS_INFO("I heard: [%s]", msg->data.c_str());

  if (msg->data.compare(str) == 0)
    ROS_INFO("Interrupt has been triggered!");
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::Empty>("toggle_led", 1000);
  ros::Subscriber sub = n.subscribe("listener", 1000, chatterCallback);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    std_msgs::Empty msg;

    // ROS_INFO("Message is being published.");

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

#include <sstream>

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::Empty>("toggle_led", 1000);
  ros::Subscriber sub1 = n.subscribe("chatter1", 1000, chatterCallback);
  ros::Subscriber sub2 = n.subscribe("chatter2", 1000, chatterCallback);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    std_msgs::Empty msg;

    // std::stringstream ss;
    // ss << "hello world " << count;
    // msg.data = ss.str();

    ROS_INFO("Message is being published.");

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
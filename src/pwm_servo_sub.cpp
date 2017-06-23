/*
This program is used for testing the control of two motors simultaneously 
with Arduino Uno and TeensyLC boards. It will publish the message to control 
servo as well as a DC motor.

To control the servo motor the angle to which servo is supposed to move 
has to be published. This angle has to be in the range 0 to 180 degrees 
and cannot be out of this range.

To control the DC motor controlled by MD10C R3 motor driver, a custom
message has been created. This message contains the information
regarding the direction of rotation along with the speed of rotation.
The physical connections of the motors has to be done according to 
Sign Magnitude mode of the motor driver.

NOTE: The method to control a DC motor depends on the motor driver 
being used and thus care should be taken about what to publish in order
to control it. 
*/


#include "ros/ros.h"
#include "std_msgs/UInt8.h"
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
  ros::Publisher servoPub = n.advertise<std_msgs::UInt8>("servo_angle", 1000);
  ros::Subscriber sub = n.subscribe("listener", 1000, chatterCallback);

  ros::Rate loop_rate(20);

  ros_arduino_trial::pwm_signal signal;
  std_msgs::UInt8 angle;

  signal.dir = 0;
  signal.data = 0;
  angle.data = 0;

  while (ros::ok()){

    for (int i=1; i<=18; i++){
      if (i>9) {
        signal.dir = 1;
      } else {
        signal.dir = 0;
      }
      signal.data = 200;
      angle.data = angle.data + 10;
      pwmPub.publish(signal);
      servoPub.publish(angle);
      ros::spinOnce();
      loop_rate.sleep();
    }

  }
  signal.dir = 0;
  signal.data = 0;
  angle.data = 0;
  pwmPub.publish(signal);
  servoPub.publish(angle);

  ROS_INFO("Testing completed.");


  return 0;
}
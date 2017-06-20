#include <ros.h>
#include <std_msgs/String.h>

#define push_button 12
#define led 13

ros::NodeHandle nh;
std_msgs::String str_msg;

ros::Publisher chatter("chatter", &str_msg);

char roco[] = "I am RoCo!";
char hello[] = "Hello World!";
bool flag;

void ISR_push_button(){
  if (flag == true) {
    str_msg.data = roco;
    digitalWrite(led, 1);
    flag = !flag;
  } else {
    str_msg.data = hello;
    digitalWrite(led, 0);
    flag = !flag;
  }
}

void setup() {
  pinMode(push_button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  attachInterrupt(push_button, ISR_push_button, FALLING);
  flag = false;

  nh.initNode();
  nh.advertise(chatter);

}

void loop() {
  chatter.publish(&str_msg);
  delay(2);
  nh.spinOnce();

}

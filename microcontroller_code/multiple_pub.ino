
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}

ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb );
std_msgs::String str_msg1;
std_msgs::String str_msg2;
ros::Publisher chatter1("chatter1", &str_msg1);
ros::Publisher chatter2("chatter2", &str_msg2);

char hello[13] = "hello world!";
char roco[] = "I am RoCo!";

void setup()
{ 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter1);
  nh.advertise(chatter2);
}

void loop()
{  
  str_msg1.data = hello;
  chatter1.publish( &str_msg1 );
  delay(2);
  str_msg2.data = roco;
  chatter2.publish( &str_msg2 );
  nh.spinOnce();
  delay(2);
}


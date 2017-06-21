#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("listener", &str_msg);

char roco[] = "I am RoCo!";

Servo servo;

void servo_cb( const std_msgs::UInt16& cmd_msg){
  servo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<std_msgs::UInt16> sub("servo_angle", servo_cb);

void setup(){
  Serial.begin(57600);
  
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
  
  servo.attach(9); //attach it to pin 9
}

void loop(){
  str_msg.data = roco;
  chatter.publish( &str_msg );
  delay(2);
  nh.spinOnce();
  delay(1);
}

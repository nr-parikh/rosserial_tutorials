#include<ros.h>
#include<std_msgs/UInt16.h>
#include<std_msgs/String.h>

#define pwm 2
#define dir 3

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("listener", &str_msg);

char roco[] = "I am RoCo!";

void pwm_cb(const std_msgs::UInt16& pwm_msg){
  analogWrite(dir, pwm_msg.data);
  digitalWrite(13, HIGH-digitalRead(13));
//  delay(100);
}

ros::Subscriber<std_msgs::UInt16> sub("pwm_signal", pwm_cb);

void setup() {

  pinMode(pwm, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(57600);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);

}

void loop() {

  digitalWrite(pwm,HIGH);

  str_msg.data = roco;
  chatter.publish( &str_msg );
  delay(2);
  nh.spinOnce();
  delay(1);  

}

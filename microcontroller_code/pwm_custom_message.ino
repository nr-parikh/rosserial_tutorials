#include<ros.h>
#include<ros_arduino_trial/pwm_signal.h>
#include<std_msgs/String.h>

#define pwm 3
#define dir_flag 2

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("listener", &str_msg);

char roco[] = "I am RoCo!";

void pwm_cb(const ros_arduino_trial::pwm_signal& pwm_msg){
  digitalWrite(dir_flag, pwm_msg.dir);
  analogWrite(pwm, pwm_msg.data);
}

ros::Subscriber<ros_arduino_trial::pwm_signal> sub("pwm_signal", pwm_cb);

void setup() {

  pinMode(pwm, OUTPUT);
  pinMode(dir_flag, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(57600);

  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);

}

void loop() {

  str_msg.data = roco;
  chatter.publish( &str_msg );
  delay(2);
  nh.spinOnce();
  delay(1);  

}

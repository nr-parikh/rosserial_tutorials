#include <Servo.h> 
#include<ros.h>
#include<ros_arduino_trial/pwm_signal.h>
#include<std_msgs/String.h>
#include<std_msgs/UInt8.h>

#define pwm 3
#define dir_flag 2

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("listener", &str_msg);

char roco[] = "I am RoCo!";

Servo servo;

void pwm_cb(const ros_arduino_trial::pwm_signal& pwm_msg){
  digitalWrite(dir_flag, (pwm_msg.dir ? 1: 0));
  analogWrite(pwm, pwm_msg.data);
}

void servo_cb( const std_msgs::UInt8& cmd_msg){
  servo.write(cmd_msg.data); 
}


ros::Subscriber<ros_arduino_trial::pwm_signal> sub1("pwm_signal", pwm_cb);
ros::Subscriber<std_msgs::UInt8> sub2("servo_angle", servo_cb);

void setup() {

  pinMode(pwm, OUTPUT);
  pinMode(dir_flag, OUTPUT);

  Serial.begin(57600);

  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.advertise(chatter);

  servo.attach(9);

  digitalWrite(dir_flag, 0);
  digitalWrite(pwm, 0);
  servo.write(0);

}

void loop() {

  str_msg.data = roco;
  chatter.publish( &str_msg );
  delay(2);
  nh.spinOnce();
  delay(1);  

}

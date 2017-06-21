#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#define push_button 12
#define led 13

ros::NodeHandle nh;
std_msgs::String str_msg;
char roco[] = "I am RoCo!";
char hello[] = "Hello World!";
bool flag;

void messageCb( const std_msgs::Empty& toggle_msg){
  if (flag == true){
    digitalWrite(led, 1);   
  } else {
    digitalWrite(led, 0);
  }
}

ros::Publisher chatter("listener", &str_msg);
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );

void ISR_push_button(){
  static uint32_t last = 0;
  if (millis() - last > 50){
    last = millis();
    flag = !flag;
  }
}

void setup() {
  pinMode(push_button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(push_button), ISR_push_button, RISING);
  flag = false;

  Serial.begin(57600);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);

}

void loop() {
  
  if (flag == true) {
    str_msg.data = roco;
  } else {
    str_msg.data = hello;
  }
  chatter.publish(&str_msg);
  delay(2);
  nh.spinOnce();
  delay(2);

}

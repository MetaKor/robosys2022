#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>


// ++++++++++++++++++++++++++++++ TO RUN THIS NODE: +++++++++++++++++++++++++++
// Start roscore, then inititalize rosserial using: [Note USB port may change]
//     rosrun rosserial_python serial_node.py /dev/ttyACM0
// Then publish a Twist message to the topic using:
//     rostopic pub cmd_vels geometry_msgs/Twist -- '[0.0, 0.0, 0.0]' '[0.0, 0.0, 0.0]'

Servo left;
Servo right;



#define LEFT 9
#define RIGHT 10

float wheelbase = 0.2;   // m, measured

ros::NodeHandle motor_node;

geometry_msgs::Twist cmd_vels;


void msgCallback(const geometry_msgs::Twist& cmd_vels) {
  float cmd_lin_vel = cmd_vels.linear.x;
  float cmd_ang_vel = cmd_vels.angular.z;
  
  // Translate commanded velocities to duty cycles

  float left_vel  = cmd_lin_vel - cmd_ang_vel*(wheelbase*0.5);
  float right_vel = cmd_lin_vel + cmd_ang_vel*(wheelbase*0.5);

  int left_duty  = 127 + round( 127.0 * (left_vel / 0.76) );
  int right_duty = 127 + round( 127.0 * (right_vel / 0.76) );

  if (left_duty > 255) {
    left_duty = 255;
  }
  if (left_duty < 0) {
    left_duty = 0;
  }
  if (right_duty > 255) {
    right_duty = 255;
  }
  if (right_duty < 0) {
    right_duty = 0;
  }

  left.write(map(left_duty, 0, 255, 40, 140));
  right.write(map(right_duty, 0, 255, 40, 140));
  
  //analogWrite(LEFT, left_duty);
  //analogWrite(RIGHT, right_duty);
}

ros::Subscriber <geometry_msgs::Twist> vel_subscriber("/cmd_vels", &msgCallback);


void setup()
{
  left.attach(9);
  right.attach(10);

  left.write(90);
  right.write(90);

  //pinMode(LEFT, OUTPUT);
  //pinMode(RIGHT, OUTPUT);

  // Initialize motors at stopped
  //analogWrite(LEFT, 127);
  //analogWrite(RIGHT, 127);

  motor_node.initNode();
  motor_node.subscribe(vel_subscriber);
}


void loop()
{
  //left.write(120);
  //right.write(120);
  //analogWrite(LEFT, 127);
  //analogWrite(RIGHT, 127);
  motor_node.spinOnce(); 
}

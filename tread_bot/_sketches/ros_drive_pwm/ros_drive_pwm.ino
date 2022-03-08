#include <ros.h>
#include <geometry_msgs/Twist.h>


// ++++++++++++++++++++++++++++++ TO RUN THIS NODE: +++++++++++++++++++++++++++
// Start roscore, then inititalize rosserial using: [Note USB port may change]
//     rosrun rosserial_python serial_node.py /dev/ttyACM0
// Then publish a Twist message to the topic using:
//     rostopic pub cmd_vels geometry_msgs/Twist -- '[0.0, 0.0, 0.0]' '[0.0, 0.0, 0.0]'


#define LEFT 9
#define RIGHT 10

float wheelbase = 20.0; // cm NEED TO ACTUALLY MEASURE

ros::NodeHandle motor_node;

geometry_msgs::Twist cmd_vels;


void msgCallback(const geometry_msgs::Twist& cmd_vels) {
  float cmd_lin_vel = cmd_vels.linear.x;
  float cmd_ang_vel = cmd_vels.angular.z;
  
  // Translate commanded velocities to duty cycles

  // left_vel   = cmd_lin_vel - cmd_ang_vel*(wheelbase*0.5);
  // right_duty = cmd_lin_vel + cmd_ang_vel*(wheelbase*0.5);

  // left_duty  = left_vel * 500;
  // right_duty = right_vel * 500;

  analogWrite(LEFT, cmd_lin_vel);  //left_duty);
  analogWrite(RIGHT, cmd_ang_vel);  //right_duty);
}

ros::Subscriber <geometry_msgs::Twist> vel_subscriber("/cmd_vels", &msgCallback);


void setup()
{
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);

  // Initialize motors at stopped
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);

  motor_node.initNode();
  motor_node.subscribe(vel_subscriber);
}


void loop()
{
  motor_node.spinOnce(); 
}

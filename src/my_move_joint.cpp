#include "ros/ros.h"
#include "std_msgs/Float64.h"

double prevPos = 0.0;
ros::Publisher pubJoint;

void jointCallback(const std_msgs::Float64::ConstPtr& msg);

int main(int argc, char **argv){
	ros::init(argc, argv, "my_move_joint");

	ros::NodeHandle n1;
	ros::NodeHandle nh;

	ros::Subscriber float64Sub = n1.subscribe("my_float64_topic", 1000, jointCallback);
	pubJoint = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100);

	ros::Rate loop_rate(10);


	while (ros::ok()) {

        loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}

void jointCallback(const std_msgs::Float64::ConstPtr& msg) {

	if (msg->data > prevPos) {
		pubJoint.publish(msg);

		prevPos = msg->data;
	}

	ros::spinOnce();
}
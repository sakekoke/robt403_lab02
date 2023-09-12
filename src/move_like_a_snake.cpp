#include "ros/ros.h"
#include "std_msgs/Float64.h"

double PI = 3.1415926535897;

ros::Publisher pubJoint1;
ros::Publisher pubJoint2;
ros::Publisher pubJoint3;
ros::Publisher pubJoint4;
ros::Publisher pubJoint5;


double getPos(double amplitude, double freq, double t);


int main(int argc, char **argv){
	ros::init(argc, argv, "move_like_a_snake");

	ros::NodeHandle nh1;
	ros::NodeHandle nh2;
	ros::NodeHandle nh3;
	ros::NodeHandle nh4;
	ros::NodeHandle nh5;


	pubJoint1 = nh1.advertise<std_msgs::Float64>("/motortom2m/command", 100);
	pubJoint2 = nh2.advertise<std_msgs::Float64>("/joint2/command", 100);
	pubJoint3 = nh3.advertise<std_msgs::Float64>("/joint4/command", 100);
	pubJoint4 = nh4.advertise<std_msgs::Float64>("/joint6/command", 100);
	pubJoint5 = nh5.advertise<std_msgs::Float64>("/end/command", 100);


	ros::Rate loop_rate(10);

	std_msgs::Float64 msg;


	while (ros::ok()) {

		double t = ros::Time::now().toSec();
		double freq = 0.4;
		double period = 1.0 / freq;
		double half_period = period / 2.0;
		double amplitude = 0.25;
		
		msg.data = getPos(amplitude, freq, t);
		pubJoint1.publish(msg);

		msg.data = getPos(amplitude * 2, freq, t + half_period);
		pubJoint2.publish(msg);

		msg.data = getPos(amplitude * 2, freq, t);
		pubJoint3.publish(msg);

		msg.data = getPos(amplitude * 2, freq, t + half_period);
		pubJoint4.publish(msg);

		msg.data = getPos(amplitude * 2, freq, t);
		pubJoint5.publish(msg);
		
		loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}

double getPos(double amplitude, double freq, double t) {
	return amplitude * sin(2 * PI * freq * t);
}
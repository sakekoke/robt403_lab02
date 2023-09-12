#include "ros/ros.h"
#include "std_msgs/Float64.h"

ros::Publisher pubJoint;

int main(int argc, char **argv){
	ros::init(argc, argv, "move_in_square_wave");

	ros::NodeHandle nh;;

	pubJoint = nh.advertise<std_msgs::Float64>("/end/command", 100);


	ros::Rate loop_rate(10);

	std_msgs::Float64 msg;

	while (ros::ok()) {
		double t = ros::Time::now().toSec();
		double freq = 0.1;
		double period = 1.0 / freq;
		double half_period = period / 2.0;
		
		msg.data = fmod(t, period) < half_period ? 1 : -1;
		
		pubJoint.publish(msg);
		
        loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}
/**
 * ROS node that was created by Gerson Uriarte
 * 
 * uses mavROS to send a land the drone
 * 
 * Made specifically for simulation, but should work on an actual drone
 * with a companion computer
 */


#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

State current_state;

//takes information published to current state topic and saves it to be used locally
void state_callback(const State::ConstPtr& msg){
    current_state = *msg;
}

int main(int argc, char **argv){
    ros::init(argc, argv, NODE_NAME);
    ros::NodeHandle nh;

    //Creates a subscriber to the mavros/state topic and points it to the state_callback function
    ros::Subscriber state_subscriber = nh.subscribe<State>("mavros/state", 10, state_callback);

    //publishes to the mavros/setpoint_position/local
    ros::Publisher local_position_publisher = nh.subscribe<PoseStamped>("mavros/setpoint_position/local", 10);

    //service that arms the drone for us
    ros::ServiceClient arming_client = nh.serviceClient<CommandBool>("mavros/cmd/arming");

    //service that sets the flight mode of the drone
    ros::ServiceClient = set_mode_client = nh.serviceClient<SetMode>("mavros/set_mode");

    //sets the rate at which the node will publish / pull from topics
    ros::Rate rate(NODE_RATE);

    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    PoseStamped pose;
    pose.pose.position.x = ?;
    pose.pose.position.x = ?;
    pose.pose.position.z = ?;

}
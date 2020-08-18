/**
 * ROS node that was created by Gerson Uriarte
 * 
 * uses mavROS to send a land the drone
 * 
 * Made specifically for simulation, but should work on an actual drone
 * with a companion computer
 */

#include "examples/land_node.h"

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
    ros::Publisher local_position_publisher = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);

    //service that arms the drone for us
    ros::ServiceClient arming_client = nh.serviceClient<CommandBool>("mavros/cmd/arming");

    //service that sets the flight mode of the drone
    ros::ServiceClient set_mode_client = nh.serviceClient<SetMode>("mavros/set_mode");

    //sets the rate at which the node will publish / pull from topics
    ros::Rate rate(NODE_RATE);

    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.x = 0;
    pose.pose.position.z = 0;

    //populate the topic a little bit before beginning the actual publishing, stops weird things
    //from happening
    for(int i = 0; ros::ok() && i < 100; ++i){
        local_position_publisher.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    //sets the mode to offboard
    SetMode offboard;
    offboard.request.custom_mode = "OFFBOARD";

    //arms the vehicle
    CommandBool arm;
    arm.request.value = true;

    ros::Time last_request = ros::Time::now();

    //checks to see if the px4 is armed in offboard, if it is then send the necessary message
    while(ros::ok()){
        if(current_state.mode != "OFFBOARD" && (ros::Time::now() - last_request > ros::Duration(5))){
            if(set_mode_client.call(offboard) && offboard.response.mode_sent){
                ROS_INFO("OFFBOARD enabled");
            }
            last_request = ros::Time::now();

        } else {
            if(!current_state.armed && (ros::Time::now() - last_request > ros::Duration(5))){
                if(arming_client.call(arm) && arm.response.success){
                    ROS_INFO("Vehicle is armed");
                }
                last_request = ros::Time::now();
            }
        }

        local_position_publisher.publish(pose);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;

}
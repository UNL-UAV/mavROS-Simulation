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


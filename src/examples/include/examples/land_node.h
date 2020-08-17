/**
 * Header file to define and construct values for the land_node.cpp
 * 
 * used to clean up the code and make it easier to read and understand
 */


#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#define NODE_NAME "land_node"
#define NODE_RATE 20

#typedef geometry_msgs::PoseStamped PoseStamped;
#typedef mavros_msgs::CommandBool CommandBool;
#typedef mavros_msgs::SetMode SetMode;
#typedef amvros_msgs::State State;


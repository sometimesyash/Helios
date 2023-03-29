#include "rosControl.h"
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <hector_mapping/hector_mapping.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/TransformStamped.h>
#include <map_server/map_server.h>

void getMap(const nav_msgs::OccupancyGrid::ConstPtr& msg){

    ros::NodeHandle nodeHandler;
    ros::ServiceClient client = nodeHandler.serviceClient<nav_msgs::GetMap>("static_map");

    nav_msgs::GetMap result;

    if(client.call(result)){
        //If the system is valid

        map_server::MapSaver::Request requ;
        map_server::MapSaver::Response respo;

        requ.map = result.response.map;
        requ.name = "instant_map_result";
        map::server::MapSaver::serviceCallback(requ, respo);
        //Saving the static map output as a file;


    }

}

void getPos(const geometry_msgs::TransformStamped::ConstPtr& pose_msg){

    float x = pose_msg->position.x;
    float y = pose_msg->position.y;
    float z = pose_msg->position.z;
    float qx = pose_msg->orientation.x;
    float qy = pose_msg->orientation.y;
    float qz = pose_msg->orientation.z;
    float qw = pose_msg->orientation.w;

    kalmanFilter(x, y, z);



}

void runRos(void* ignore){ //Asynchronous Style Decleration

    int main(int argc, char** argv){
        ros::init(argc, argv, "map_processing_node");

        ros::NodeHandle handler;

       ros::Subscriber sub_map = nh.subscribe<nav_msgs::OccupancyGrid>("/map", 10, mapCallback);
       ros::spin();
       
       return 0;
    }   

}


#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

  ros::init(argc, argv, "pick_objects");

 
  MoveBaseClient ac("move_base", true);

 
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  
  goal.target_pose.pose.position.x = -2.4;
  goal.target_pose.pose.position.y = 0.23;
  goal.target_pose.pose.orientation.w = -0.25;

   
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

 
  ac.waitForResult();
 
  
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base reached the pickup zone");
  else
    ROS_INFO("The base failed to reach the pickup zone for some reason");
   ros::Duration(5.0).sleep();

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting 5 seconds after reaching the pickup zone");
  }
 
  
  goal.target_pose.pose.position.x = 0.2;
  goal.target_pose.pose.position.y = -2.3;
  goal.target_pose.pose.orientation.w = 1.13;

  
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

 
  ac.waitForResult();

 
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base reached the dropoff zone");
  else
    ROS_INFO("The base failed to reach the dropoff zone for some reason");

  return 0;
}

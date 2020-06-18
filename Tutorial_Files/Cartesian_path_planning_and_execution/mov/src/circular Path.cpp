
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <rviz_visual_tools/rviz_visual_tools.h>

#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <math.h>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "moveit_robot");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  //rviz visual tools
  rviz_visual_tools::RvizVisualToolsPtr visual_tools_;

  static const std::string PLANNING_GROUP = "arm";

  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  const robot_state::JointModelGroup *joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_footprint");
  visual_tools.deleteAllMarkers();
  visual_tools_.reset(new rviz_visual_tools::RvizVisualTools("base_footprint", "/rviz_visual_markers"));

  Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
  text_pose.translation().z() = 1.75;

  geometry_msgs::Pose tempPose;
  tempPose.position.z = 0.5;
  tempPose.position.y = 0.2;
  tempPose.orientation.x = 0;

  std::vector<geometry_msgs::Pose> waypoints;

  Json::Reader reader;
  Json::Value root;
  std::ifstream file("/home/i/catkin_ws/src/mov/src/points.json");
  file >> root;

  double radious = 0.002;
  double PI = 3.14159;
  for (double angle = 0; angle <= 2 * PI; angle += 0.02)
  {
    tempPose.position.y += radious * sin(angle);
    tempPose.position.x += radious * cos(angle);
    waypoints.push_back(tempPose);
  }

  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);

  //visual_tools.deleteAllMarkers();
  visual_tools.publishPath(waypoints, rvt::GREEN, rvt::SMALL);
  visual_tools.trigger();
  visual_tools.prompt("");
}
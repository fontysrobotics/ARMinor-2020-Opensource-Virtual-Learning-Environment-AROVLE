#include "ros/ros.h"

#include <sensor_msgs/JointState.h>

class HectorJointStatePublisher{
public:
  HectorJointStatePublisher()
  {
    joint_name_vector.push_back("joint1");
    

    out_joint_state_.name.resize(joint_name_vector.size());
    out_joint_state_.position.resize(joint_name_vector.size());

    ros::NodeHandle nh;

    joint_state_pub_ = nh.advertise<sensor_msgs::JointState>("/joint_states",5);

    for (size_t i = 0; i < joint_name_vector.size(); ++i){
      //dyn_joint_state_subs_[i] = nh.subscribe("/" + joint_name_vector[i] + "/state", 1, &HectorJointStatePublisher::dynamixelJointStateCallback, this);
      //ros::Subscriber sub = nh.subscribe("/" + joint_name_vector[i] + "/state", 1, &HectorJointStatePublisher::dynamixelJointStateCallback, this);
      out_joint_state_.name[i] = joint_name_vector[i];
      out_joint_state_.position[i] = 1;
      map_name_to_index_[joint_name_vector[i]] = i;
    }

    ros::Duration joint_state_publish_period(1/40.0);

    joint_state_publish_timer_ = nh.createTimer(ros::Duration(joint_state_publish_period), &HectorJointStatePublisher::timerPublishJointStates, this, false );

  }

  ~HectorJointStatePublisher()
  {

  }

 

  void timerPublishJointStates(const ros::TimerEvent& e)
  {
    out_joint_state_.header.stamp = ros::Time::now();
    joint_state_pub_.publish(out_joint_state_);
  }

protected:
  std::vector<std::string> joint_name_vector;
  std::vector<ros::Subscriber> dyn_joint_state_subs_;
  ros::Publisher joint_state_pub_;
  std::map<std::string, int> map_name_to_index_;

  ros::Timer joint_state_publish_timer_;
  sensor_msgs::JointState out_joint_state_;
};


int main(int argc, char **argv){
  ros::init(argc, argv, "hector_arm_joint_state_publisher");

  HectorJointStatePublisher jp;

  ros::spin();

  return 0;
}
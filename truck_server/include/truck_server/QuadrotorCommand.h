
#ifndef QUADROTOR_COMMAND_H_
#define QUADROTOR_COMMAND_H_

/* ros */
#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>

/* linear algebra */
#include <math.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Eigenvalues>
#include <tf/transform_broadcaster.h>

/* local class */
#include <bspline_ros/bsplineGenerate.h>
#include <quadrotor_trajectory/VehicleTrajectoryBase.h>

/* general header file */
#include <iostream>

using namespace Eigen;
using namespace vehicle_trajectory_base;

class QuadrotorCommand {
public:
  QuadrotorCommand();
  virtual ~QuadrotorCommand();

  ros::NodeHandle m_nh;
  bool m_gazebo_mode;
  double m_uav_vel_ub;
  double m_uav_vel_lb;
  double m_uav_acc_ub;
  double m_uav_acc_lb;
  tf::Vector3 m_uav_world_pos;
  tf::Vector3 m_uav_world_vel;
  tf::Vector3 m_uav_world_acc;
  tf::Vector3 m_truck_world_pos;
  tf::Vector3 m_uav_truck_world_pos;
  tf::Quaternion m_uav_q;
  nav_msgs::Odometry m_truck_odom;
  /* state: 0, still; 1, taking off; 2, ready to move; 3, landing finishes */
  int m_uav_state;
  nav_msgs::Odometry m_uav_odom;
  geometry_msgs::Twist m_uav_cmd;

  // pid
  double m_traj_track_p_gain;
  double m_traj_track_i_gain;
  double m_traj_track_d_gain;
  tf::Vector3 m_traj_track_i_term_accumulation;
  double m_traj_track_p_term_max;
  double m_traj_track_i_term_max;
  double m_traj_track_d_term_max;
  double m_uav_yaw_i_term_accumulation;
  double m_uav_odom_freq;

  /* bspline generator */
  bsplineGenerate *m_bspline_traj_ptr;
  bool m_traj_updated;
  double m_traj_updated_time;
  VehicleTrajectoryBase m_truck_traj;

  std::string m_truck_odom_sub_topic_name;
  std::string m_uav_odom_sub_topic_name;
  std::string m_uav_cmd_pub_topic_name;

  // Subscriber
  ros::Subscriber m_sub_truck_odom;
  ros::Subscriber m_sub_uav_odom;

  // Publisher
  ros::Publisher m_pub_uav_cmd;

  void truckOdomCallback(const nav_msgs::OdometryConstPtr& truck_odom_msg);
  void uavOdomCallback(const nav_msgs::OdometryConstPtr& uav_odom_msg);
  inline double uavTruckHorizonDistance();
  void updateUavTruckRelPos();
  void trajectoryTracking(Vector3d uav_des_pos, Vector3d uav_des_vel);
  bool uavMovingToPresetHeight(double height);
  inline tf::Vector3 vectorToVector3(std::vector<double> vec);
  inline tf::Vector3 vector3dToVector3(Vector3d vec);
};

#endif

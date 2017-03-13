# octomap_truck
Iterative generating safe control polygon for bspline trajectory.

State list: state: 0, still; 1, taking off; 2, ready to move; 3, start to track; 4, wait to land; 5, start to land; 6, wait to force land; 7, start force land; 8, during force land; 9, finish force land.

State 3: start to track and land in m_uav_tracking_landing_constant_speed (~0.5m/s) to (m_uav_start_landing_height_upperbound (~5m) + m_target_height), then changes to state 4 wait to land.

When publish topic "/uav_straight_lane_landing_start_flag" or GPS point is inside trigger region (to do), uav will changes to state 5, then land in m_uav_landing_constant_speed (~1.0m/s) until landing.

Run simulator:  
  
roslaunch truck_server octomap_truck_server.launch debug:=true dji:=false uav_direct_start:=false landing:=true

1.Give command to make uav fly to 10m height. This topic please pub immediately after launch file

  rostopic pub /uav_start_flag std_msgs/Empty "{}"


2.This topic could be published after uav keeps on ~5m height and it will help uav be into start landing state

  rostopic pub /uav_straight_lane_landing_start_flag std_msgs/Empty "{}"
    

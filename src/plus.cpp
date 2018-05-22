#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <stdio.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_cv/grid_map_cv.hpp>
#include "grid_map_core/Polygon.hpp"
#include <math.h> //fabs
#include "m700_msgs/StoSlam.h"

namespace nodelet_sto
{

class Plus : public nodelet::Nodelet
{
public:
  Plus()
  : value_(0)
  {}

private:
  virtual void onInit()
  {
    ros::NodeHandle& private_nh = getPrivateNodeHandle();
    private_nh.getParam("value", value_);
    pub = private_nh.advertise<std_msgs::Float64>("out", 10);
    sub = private_nh.subscribe("in", 10, &Plus::callback, this);
    gridMapSubscriber = private_nh.subscribe("cleaned_map_grid_map",
                       10, &Plus::gridmapCallback, this);
    gridMapPublisher = private_nh.advertise<grid_map_msgs::GridMap>(
                      "GridMapOut", 10);

    Service_ = private_nh.advertiseService("sto_test_srv", &Plus::ServiceCallback, this);
  }

  void callback(const std_msgs::Float64::ConstPtr& input)
  {
    std_msgs::Float64Ptr output(new std_msgs::Float64());
    output->data = input->data + value_;
    NODELET_DEBUG("Adding %f to get %f", value_, output->data);
    pub.publish(output);
  }

  void gridmapCallback(const grid_map_msgs::GridMap &msg_grid_map)
  {
    gridMapPublisher.publish(msg_grid_map);
    NODELET_DEBUG("hi");
  }

  bool ServiceCallback(m700_msgs::StoSlam::Request &req,
         m700_msgs::StoSlam::Response &res)
  {
    res.result = true;
    return true;
  }

  ros::Publisher pub;
  ros::Subscriber sub;
  ros::Subscriber gridMapSubscriber;
  ros::Publisher gridMapPublisher;
  ros::ServiceServer Service_;
  double value_;
};

PLUGINLIB_EXPORT_CLASS(nodelet_sto::Plus,nodelet::Nodelet)
}
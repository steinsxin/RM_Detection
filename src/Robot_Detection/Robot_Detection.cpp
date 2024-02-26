#include "ros/ros.h"
#include <ros/time.h>

// 结构体
#include "protocol.h"
#include "robot_struct.h"

// 图像传输
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CompressedImage.h>
#include <image_transport/image_transport.h>

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

// msg
#include "robot_msg/Robot_ctrl.h"
#include "robot_msg/Vision.h"

// Opencv 4.5.5
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Eigen
#include <Eigen/Dense>


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    // 展示图片
    ROS_INFO("RX_YES");
    cv::Mat image = cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::imshow("HIK_Camera_Receive", image);
    cv::waitKey(1);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

cv::Mat src;
vision_t Vision_data;
void callback(const sensor_msgs::ImageConstPtr &src_msg, const robot_msg::VisionConstPtr &Vision_msg){
  
    // 读取图片
    src = cv_bridge::toCvShare(src_msg, "bgr8")->image;
    cv::imshow("HIK_Camera_Receive", src);
    cv::waitKey(1);

    // 读取IMU数据
    Vision_data.id = Vision_msg->id;
    Vision_data.mode = Vision_msg->mode;
    Vision_data.pitch = Vision_msg->pitch;
    Vision_data.yaw = Vision_msg->yaw;
    Vision_data.roll = Vision_msg->roll;
    Vision_data.shoot = Vision_msg->shoot;
    for (size_t i = 0; i < 4; i++)
    {
      Vision_data.quaternion[i] = Vision_msg->quaternion[i];
    }
    ROS_INFO("Pitch: %.2f",Vision_data.pitch);
    // 进行识别处理

    // 进行跟踪处理

    // 进行整车观测

    // 击打逻辑

    // 发送数据

}

int main(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    // 初始化节点
    ros::init(argc, argv, "Robot_Detection");

    // 创建句柄
    ros::NodeHandle nh;

    // image_transport::ImageTransport it(nh);
    // image_transport::Subscriber sub = it.subscribe("HIK_Camera/image", 1, imageCallback);
    
    // 建立需要订阅的消息对应的订阅器
    message_filters::Subscriber<sensor_msgs::Image> HIK_Camera_sub(nh, "/HIK_Camera/image", 10);  
    message_filters::Subscriber<robot_msg::Vision> Imu_sub(nh, "/Vision_data", 10);  

    // 同步ROS消息
    
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, robot_msg::Vision> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), HIK_Camera_sub, Imu_sub);

    ROS_INFO("YES");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

    return 0;

}
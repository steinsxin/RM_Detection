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

// 识别预测头文件
#include "AngleSolve.h"
#include "Armor_Track.h"
#include "Armor_Observe.h"
#include "Armor_detection.h"


// 数据部分
cv::Mat src;
form Vision_data;
ros::Publisher Vision_pub;

ArmorDetector Detector;
AngleSolve AS;
ArmorTrack Tracker;
ArmorObserve AO;
std::vector<double> vdata(4);

void callback(const sensor_msgs::ImageConstPtr &src_msg, const robot_msg::VisionConstPtr &Vision_msg){
  
    // Armor容器
    std::vector<Armor> Targets;

    // 读取图片
    src = cv_bridge::toCvShare(src_msg, "bgr8")->image;
    cv::imshow("HIK_Camera_Receive", src);
    cv::waitKey(1);

    // 读取IMU数据
    Vision_data.data[0] = Vision_msg->pitch;  // pitch
    Vision_data.data[1] = Vision_msg->yaw;    // yaw
    Vision_data.data[2] = Vision_msg->roll;   // roll
    Vision_data.mode = Vision_msg->mode;      // 0x21
    // 四元数
    for (size_t i = 0; i < 4; i++)
    {
      Vision_data.quat[i] = Vision_msg->quaternion[i];
    }
    

    ROS_INFO("Pitch: %.2f",Vision_msg->pitch);

    // 初始化四元数
    Tracker.AS.Init(Vision_data.data, Vision_data.quat);
    AO.AS.Init(Vision_data.data, Vision_data.quat);

    // 进行识别处理
    // Targets = Detector.Detection(src);
    // // 获取最终装甲板
    // Tracker.Track(src,Targets,std::chrono::high_resolution_clock::now());
    // Tracker.show();
   
    // // 整车观测
    // bool AO_OK = (Tracker.tracker_state == TRACKING) && Tracker.OB_Track[Tracker.tracking_id].is_initialized;
    // // 开始拟合圆心
    // double OK = false;
    // if(AO_OK) {
    //   double angle =  AO.spin_angle*(180.0f/CV_PI);
    //   // 左右角度
    //   // -30 -45
    //   double select_angle_left = -15;
    //   double select_angle_right = -25;
    //   if(Tracker.OB_Track[Tracker.tracking_id].axesState == Robot::LONG){
    //       AO.Angle_Speed = Tracker.Angle_Speed; 
    //       AO.Center_fitting(Tracker.enemy_armor,Tracker.OB[Tracker.tracking_id].Long_axes,Tracker.OB[Tracker.tracking_id].center_Z,Tracker.OB[Tracker.tracking_id],Tracker.OB_Track[Tracker.tracking_id]);
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Smooth_position);
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.pre_pos);
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.pre_Armor);

    //       // 根据旋转方向两确定跟踪两个点 逆时针旋转
    //       // if(AO.spin_angle*(180.0f/CV_PI) < select_angle_left && AO.spin_angle*(180.0f/CV_PI) > select_angle_right){
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.spin_Aromor);
    //       //     OK = true;
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // } 
    //       // else {
    //       //     // 改到固定点位 
    //       //     // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.right_target);
    //       //     // Tracker.Solve_pitch = rpy[1];
    //       //     // Tracker.Solve_yaw = rpy[2];
    //       //     Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
    //       //     Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
    //       // }
                    
    //       // 快速陀螺测试
    //       if(AO.Left_Armor_angle < select_angle_left && AO.Left_Armor_angle > select_angle_right){
    //           Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Left_Armor);
    //           OK = true;
    //           Tracker.Solve_pitch = rpy[1];
    //           Tracker.Solve_yaw = rpy[2];
    //       } 
    //       // 固定点位需要修改
    //       else {
    //           Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
    //           Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
    //       }

    //       // else if(AO.Left_Armor_angle < select_angle_left && AO.spin_angle*(180.0f/CV_PI) > -select_angle_right){
    //       //     Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Left_Armor);
    //       //     OK = true;
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // } 
    //       // else{
    //       //     Eigen::Vector3d rpy = AS.Barrel_Solve(AO.left_target);
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // }
    //   }
    //   else if(Tracker.OB_Track[Tracker.tracking_id].axesState == Robot::SHORT){

    //       AO.Center_fitting(Tracker.enemy_armor,Tracker.OB[Tracker.tracking_id].Long_axes,Tracker.OB[Tracker.tracking_id].center_Z,Tracker.OB[Tracker.tracking_id],Tracker.OB_Track[Tracker.tracking_id]);

    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Smooth_position);
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.pre_pos);
    //       // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.pre_Armor);

    //       // 根据旋转方向两确定跟踪两个点 逆时针旋转
    //       // if(AO.spin_angle*(180.0f/CV_PI) < select_angle_left && AO.spin_angle*(180.0f/CV_PI) > select_angle_right){
    //       //     Eigen::Vector3d rpy = AS.Barrel_Solve(AO.spin_Aromor);
    //       //     OK = true;
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // } 
    //       // else {
    //       //     // 改到固定点位 

    //       //     // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.right_target);
    //       //     // Tracker.Solve_pitch = rpy[1];
    //       //     // Tracker.Solve_yaw = rpy[2];

    //       //     Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
    //       //     Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
    //       // }
                    
    //       // 快速陀螺测试
    //       if(AO.Left_Armor_angle < select_angle_left && AO.Left_Armor_angle > select_angle_right){
    //           Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Left_Armor);
    //           OK = true;
    //           Tracker.Solve_pitch = rpy[1];
    //           Tracker.Solve_yaw = rpy[2];
    //       } 
    //       // 固定点位需要修改
    //       else {
    //           Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
    //           Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
    //       }

    //       // else if(AO.Left_Armor_angle < select_angle_left && AO.spin_angle*(180.0f/CV_PI) > -select_angle_right){
    //       //     Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Left_Armor);
    //       //     OK = true;
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // } 
    //       // else{
    //       //     Eigen::Vector3d rpy = AS.Barrel_Solve(AO.left_target);
    //       //     Tracker.Solve_pitch = rpy[1];
    //       //     Tracker.Solve_yaw = rpy[2];
    //       // }
    //       }
    //       cv::putText(src,"OK: "+ std::to_string(OK),cv::Point(0,100),cv::FONT_HERSHEY_SIMPLEX, 1,cv::Scalar(255, 255, 0),2,3);
    //       // if(AO.Fit_OK) {AO.ArmorObserve_show(AO.Smooth_position,Tracker.OB[Tracker.tracking_id],Tracker.OB_Track[Tracker.tracking_id]);}
    // }

    // 创建发送数据
    robot_msg::Robot_ctrl Robot_ctrl_t;

    // 开火判断
    // double fire;
    // if(OK) fire = 1;
    // else fire = 0;

    // 填充数据
    Robot_ctrl_t.pitch = 10;
    Robot_ctrl_t.yaw = 15;
    Robot_ctrl_t.fire_command = 0;
    Robot_ctrl_t.target_lock = 0x31;

    // 发送数据
    Vision_pub.publish(Robot_ctrl_t);


}


int main(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    // 初始化节点
    ros::init(argc, argv, "Robot_Detection");

    // 创建句柄
    ros::NodeHandle nh;

    Vision_pub = nh.advertise<robot_msg::Robot_ctrl>("Robot_ctrl_data",1);

    // image_transport::ImageTransport it(nh);
    // image_transport::Subscriber sub = it.subscribe("HIK_Camera/image", 1, imageCallback);
    
    // 建立需要订阅的消息对应的订阅器
    message_filters::Subscriber<sensor_msgs::Image> HIK_Camera_sub(nh, "/HIK_Camera/image", 1);  
    message_filters::Subscriber<robot_msg::Vision> Imu_sub(nh, "/Vision_data", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, robot_msg::Vision> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), HIK_Camera_sub, Imu_sub);

    ROS_INFO("--Robot_Detection Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

    return 0;

}
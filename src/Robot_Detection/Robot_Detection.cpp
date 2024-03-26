#include "ros/ros.h"
#include <ros/time.h>
#include <ros/package.h>

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
#include "robot_msgs/Robot_ctrl.h"
#include "robot_msgs/Vision.h"

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
#include "Neural_Armor_Detection.h"


// 数据部分
cv::Mat src;
form Vision_data;
ros::Publisher Vision_pub;

#define Neural_Detection    // 神经网络启动开关 

#ifdef Neural_Detection
NeuralArmorDetector Neural_Detector;
#else
ArmorDetector Detector;
#endif //Neural_Detection
AngleSolve AS;
ArmorTrack Tracker;
ArmorObserve AO;
std::vector<double> vdata(4);

void callback(const sensor_msgs::ImageConstPtr &src_msg, const robot_msgs::VisionConstPtr &Vision_msg){
  
    // Armor容器
    std::vector<Armor> Targets;

    // 读取图片
    src = cv_bridge::toCvShare(src_msg, "bgr8")->image;

    // 读取IMU数据
    Vision_data.enemy_color = Vision_msg->id; // 颜色
    Vision_data.data[0] = Vision_msg->pitch;  // pitch
    Vision_data.data[1] = Vision_msg->yaw;    // yaw
    Vision_data.data[2] = Vision_msg->shoot;  // shoot
    Vision_data.mode = Vision_msg->mode;      // 0x21
    // 四元数
    for (size_t i = 0; i < 4; i++)
    {
      Vision_data.quat[i] = Vision_msg->quaternion[i];
    }


    // 初始化四元数
    Tracker.AS.Init(Vision_data.data, Vision_data.quat);
    AO.AS.Init(Vision_data.data, Vision_data.quat);

    // 选择击打颜色
#ifdef Neural_Detection
    // Neural_Detector.enemy_color = Vision_data.enemy_color;
    Neural_Detector.enemy_color = BLUE;
#else 
    // Detector.enemy_color = Vision_data.enemy_color;
    Detector.enemy_color = BLUE;
#endif //Neural_Detection

    double OK = false;
    if(Vision_data.mode == 0x21)
    {
        
    // 进行识别处理
#ifdef Neural_Detection
    Targets = Neural_Detector.detect(src);
#else 
    Targets = Detector.Detection(src);
#endif //Neural_Detection
    // 获取最终装甲板
    Tracker.Track(src,Targets,std::chrono::high_resolution_clock::now());
    Tracker.show();
    cv::waitKey(1);

    // 弹道速度(后面改成发过来的弹道数据) | 有点问题,赋值的地方(测试)
    AS.bullet_speed = 25;
    Tracker.AS.bullet_speed = 25;

    // 整车观测(跟踪情况和当前跟踪车辆的观测情况)
    bool AO_OK = (Tracker.tracker_state == TRACKING) && Tracker.OB_Track[Tracker.tracking_id].is_initialized;
    // 开始拟合圆心
    if(AO_OK) {
        double angle =  AO.spin_angle*(180.0f/CV_PI);
        // 左右角度[以逆时针为基准]
        // -30 -45
        double select_angle_left = -15;
        double select_angle_right = -25;
    
        AO.Angle_Speed = Tracker.Angle_Speed; 
        AO.Spin_State = Tracker.Spin_State();
        AO.Center_fitting(Tracker.enemy_armor,Tracker.OB[Tracker.tracking_id].center_Z,Tracker.OB[Tracker.tracking_id],Tracker.OB_Track[Tracker.tracking_id]);

        // 转速调节陀螺模式[0.10~0.2][0.2~0.35]?
        if(Tracker.Angle_Speed > 0.10 && Tracker.Angle_Speed < 0.2){

            // 判断陀螺状态
            if((Tracker.Spin_State() == COUNTER_CLOCKWISE) || (Tracker.Spin_State() == CLOCKWISE)){
                // 逆时针[L] 顺时针[R] 击打当前装甲板不需要区分
                if(AO.spin_angle*(180.0f/CV_PI) < select_angle_left && AO.spin_angle*(180.0f/CV_PI) > select_angle_right){
                    Eigen::Vector3d rpy = AS.Barrel_Solve(AO.spin_Aromor);
                    OK = true;
                    Tracker.Solve_pitch = rpy[1];
                    Tracker.Solve_yaw = rpy[2];
                } 
                else {
                    // 改到固定点位？需要顺逆时针
                    // Eigen::Vector3d rpy = AS.Barrel_Solve(AO.right_target);
                    // Tracker.Solve_pitch = rpy[1];
                    // Tracker.Solve_yaw = rpy[2];
                    Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
                    Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
                }   
            }
            else{
                // 退出陀螺模式
                Tracker.Angle_Speed = 0;
            }
            
        }
        else if(Tracker.Angle_Speed > 0.20 && Tracker.Angle_Speed < 0.35)
        {
            // 逆时针[L]
            if(Tracker.Spin_State() == COUNTER_CLOCKWISE){
                // 快速陀螺测试
                if(AO.Left_Armor_angle < select_angle_left && AO.Left_Armor_angle > select_angle_right){
                    Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Left_Armor);
                    OK = true;
                    Tracker.Solve_pitch = rpy[1];
                    Tracker.Solve_yaw = rpy[2];
                } 
                // 固定点位需要修改
                else {
                    Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
                    Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
                }
            }
            // 顺时针[R] 陀螺状态判断上还有点问题
            else if (Tracker.Spin_State() == CLOCKWISE)
            {
                // 快速陀螺测试
                if(AO.Right_Armor_angle > -select_angle_left && AO.Right_Armor_angle < -select_angle_right){
                    Eigen::Vector3d rpy = AS.Barrel_Solve(AO.Right_Armor);
                    OK = true;
                    Tracker.Solve_pitch = rpy[1];
                    Tracker.Solve_yaw = rpy[2];
                } 
                // 固定点位需要修改
                else {
                    Tracker.Solve_pitch = Tracker.AS.Robot_msg.Controller_pitch;
                    Tracker.Solve_yaw = Tracker.AS.Robot_msg.Controller_yaw;
                }
            }
            else{
                // 退出陀螺模式
                Tracker.Angle_Speed = 0;
            }
        }else if (Tracker.Angle_Speed > 0.35)
        {  // 最快陀螺速度

        }
            
        cv::putText(src,"OK: "+ std::to_string(OK),cv::Point(0,100),cv::FONT_HERSHEY_SIMPLEX, 1,cv::Scalar(255, 255, 0),2,3);
        // if(AO.Fit_OK) {AO.ArmorObserve_show(AO.Smooth_position,Tracker.OB[Tracker.tracking_id],Tracker.OB_Track[Tracker.tracking_id]);}
    }
    }
    


    // 创建发送数据
    robot_msgs::Robot_ctrl Robot_ctrl_t;

    // 开火判断
    double fire;
    if(OK) fire = 1;
    else fire = 0;

    // 填充数据
    if(Tracker.tracker_state == TRACKING){
        Robot_ctrl_t.pitch = Tracker.Solve_pitch;
        Robot_ctrl_t.yaw = Tracker.Solve_yaw;
        Robot_ctrl_t.fire_command = fire;
        Robot_ctrl_t.target_lock = 0x31;
    }else {
        Robot_ctrl_t.pitch = Tracker.AS.Robot_msg.Controller_pitch;
        Robot_ctrl_t.yaw = Tracker.AS.Robot_msg.Controller_yaw;
        Robot_ctrl_t.fire_command = 0;
        Robot_ctrl_t.target_lock = 0x32;
    }

    // 发送数据
    Vision_pub.publish(Robot_ctrl_t);
}


int main(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    // 初始化节点
    ros::init(argc, argv, "Robot_Detection");

    // 创建句柄
    ros::NodeHandle nh;

    Vision_pub = nh.advertise<robot_msgs::Robot_ctrl>("Robot_ctrl_data",1);

    // 建立需要订阅的消息对应的订阅器
    message_filters::Subscriber<sensor_msgs::Image> HIK_Camera_sub(nh, "/HIK_Camera/image", 1);  
    message_filters::Subscriber<robot_msgs::Vision> Imu_sub(nh, "/Vision_data", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, robot_msgs::Vision> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), HIK_Camera_sub, Imu_sub);
    
    ROS_INFO("--Robot_Detection Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

    return 0;

}
#include "ros/ros.h"
#include <ros/time.h>

// msg
#include "robot_msgs/robot_ctrl.h"
#include "robot_msgs/PTZ_Yaw.h"
#include "robot_msgs/PTZ_perception.h"
#include "std_msgs/Float32.h"
#include "std_msgs/UInt8.h"

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

// Kalman
#include "Kalman.h"

ros::Publisher Robot_L_ctrl_pub;
ros::Publisher Robot_R_ctrl_pub;
ros::Publisher Robot_main_yaw_pub;


// 击打模式切换
typedef enum
{
    Same_target = 10,          // 相同目标击打
    Different_target = 20,     // 独立目标击打
    Base_Strike = 3           // 基地不击打模式(暂定)
}Strike_Mode;

int Mode = Same_target;       // 等待接口接入
float main_yaw;
float Decision_pitch_L;
float Decision_pitch_R;
float Decision_Yaw_L;
float Decision_Yaw_R;
float Decision_Yaw_count;
int Decision_fire_command_L;
int Decision_fire_command_R;
int Decision_fire_mode_L;
int Decision_fire_mode_R;
int Decision_target_lock_L;
int Decision_target_lock_R;

Kalman kalman_yaw_L;
Kalman kalman_pitch_L;
Kalman kalman_yaw_R;
Kalman kalman_pitch_R;
Kalman kalman_yaw_main;

// 计算yaw轴数据,进行控制处理
void callback(const robot_msgs::PTZ_perceptionConstPtr &PTZ_L, const robot_msgs::PTZ_perceptionConstPtr &PTZ_R){

    // 0x31表示跟踪,0x32表示丢失
    int target_lock_L = PTZ_L->target_lock;
    int target_lock_R = PTZ_R->target_lock;

    bool situation_1 = (target_lock_L == 0x31) && (target_lock_R == 0x31);  // 情况1
    bool situation_2 = (target_lock_L == 0x31) && (target_lock_R == 0x32);  // 情况2
    bool situation_3 = (target_lock_L == 0x32) && (target_lock_R == 0x31);  // 情况3

    // 大Yaw轴
    float Yaw_count;

    // 计算两个小云台yaw轴移动角度(相对于大云台的yaw轴角度)
    float Yaw_L;
    float Yaw_R;
    Yaw_L = PTZ_L->yaw - main_yaw;
    Yaw_R = PTZ_R->yaw - main_yaw;

    // 击打同一目标则比对两个装甲板分数,不同目标则已经通过云台|全向感知融合节点进行修正

    // 击打同一目标 [切换统一目标]
    if(Mode == Same_target)
    {
        // 进行装甲板分数决策,更新两边云台的跟踪目标
        if(PTZ_L->score > PTZ_R->score){
            // 左云台情况 [绝对角]
            Yaw_R = Yaw_L;
            Yaw_count = PTZ_L->yaw;
        }else{
            // 右云台情况 [绝对角]
            Yaw_L = Yaw_R;
            Yaw_count = PTZ_R->yaw;
        }
    }
    // 独立击打目标 [不进行处理]
    else if (Mode == Different_target)
    {
        // 计算大云台Yaw轴移动角度
        if(situation_1){
            Yaw_count = (PTZ_L->yaw + PTZ_R->yaw) / 2.0f;
        }
        else if(situation_2){
            Yaw_count = (PTZ_L->yaw);
        }
        else if(situation_3){
            Yaw_count = (PTZ_R->yaw);
        }else {
            // 无跟踪情况
            Yaw_count = main_yaw;
        }
    }
    

    // // 创建发送数据
    // robot_msgs::robot_ctrl Robot_L_ctrl_t;
    // robot_msgs::robot_ctrl Robot_R_ctrl_t;
    // std_msgs::Float32 Robot_main_yaw_t;


    // 大Yaw轴数据
    // Robot_main_yaw_t.data = Yaw_count;

    // //左右开火命令
    // Robot_L_ctrl_t.fire_command = PTZ_L->fire_command;
    // Robot_R_ctrl_t.fire_command = PTZ_R->fire_command;
    // // 左右开火模式
    // Robot_L_ctrl_t.fire_mode = PTZ_L->fire_mode;
    // Robot_R_ctrl_t.fire_mode = PTZ_R->fire_mode;
    // // 左右yaw轴数据
    // Robot_L_ctrl_t.yaw = -Yaw_L;
    // Robot_R_ctrl_t.yaw = Yaw_R;
    // // 左右pitch轴数据
    // Robot_L_ctrl_t.pitch = PTZ_L->pitch;
    // Robot_R_ctrl_t.pitch = PTZ_R->pitch;
    // // 左右跟踪情况
    // Robot_L_ctrl_t.is_follow = PTZ_L->target_lock;
    // Robot_R_ctrl_t.is_follow = PTZ_R->target_lock;

    Decision_pitch_L = PTZ_L->pitch;
    Decision_pitch_R = PTZ_R->pitch;
    Decision_Yaw_L = -(PTZ_L->yaw - main_yaw);
    Decision_Yaw_R =  (PTZ_R->yaw - main_yaw);
    Decision_Yaw_count = Yaw_count;
    Decision_fire_command_L = PTZ_L->fire_command;
    Decision_fire_command_R = PTZ_R->fire_command;
    Decision_fire_mode_L = PTZ_L->fire_mode;
    Decision_fire_mode_R = PTZ_R->fire_mode;
    Decision_target_lock_L = PTZ_L->target_lock;
    Decision_target_lock_R = PTZ_R->target_lock;

    // // 发送数据
    // Robot_L_ctrl_pub.publish(Robot_L_ctrl_t);
    // Robot_R_ctrl_pub.publish(Robot_R_ctrl_t);
    // Robot_main_yaw_pub.publish(Robot_main_yaw_t);
}

// 获取大yaw轴数据
void Robot_Main_Yaw(const std_msgs::Float32ConstPtr &Yaw){
    main_yaw = Yaw->data;
}

// 获取模式
void Vision_mode(const std_msgs::UInt8ConstPtr &Vision_Mode){
    Mode = Vision_Mode->data;
}

// 左云台独立自瞄 | 离线模式下直接控制大yaw轴
void PTZ_L_Auto(const robot_msgs::PTZ_perceptionConstPtr &PTZ_L){

    // 对ROS时间戳的判断

    // 创建发送数据
    robot_msgs::robot_ctrl Robot_L_ctrl_t;

    // 左右开火命令
    Robot_L_ctrl_t.fire_command = PTZ_L->fire_command;
    // 左右开火模式
    Robot_L_ctrl_t.fire_mode = PTZ_L->fire_mode;
    // 左右yaw轴数据
    Robot_L_ctrl_t.yaw = PTZ_L->yaw;
    // 左右pitch轴数据
    Robot_L_ctrl_t.pitch = PTZ_L->pitch;
    // 左右跟踪情况
    Robot_L_ctrl_t.is_follow = PTZ_L->target_lock;

    // 发送数据
    Robot_L_ctrl_pub.publish(Robot_L_ctrl_t);
}


// 右云台独立自瞄
void PTZ_R_Auto(const robot_msgs::PTZ_perceptionConstPtr &PTZ_R){

}


// 同步左右云台的yaw轴数据和大云台的yaw轴数据,进行数据处理
int main(int argc, char *argv[]){

    // 设置语言运行环境
    setlocale(LC_ALL,"");  

    // 初始化节点
    ros::init(argc, argv, "Yaw_Communication_sync");

    // 创建句柄
    ros::NodeHandle nh;
    
    // 创建订阅对象
    ros::Subscriber main_yaw_sub = nh.subscribe<std_msgs::Float32>("/main_yaw",1,Robot_Main_Yaw);   
    ros::Subscriber mode_sub = nh.subscribe<std_msgs::UInt8>("/attack_mode",1,Vision_mode);   
    
    // 独立自瞄部分
    // ros::Subscriber PTZ_L_Auto_sub = nh.subscribe<robot_msgs::PTZ_perception>("/PTZ_L/PTZ_perception",1,PTZ_L_Auto);   
    // ros::Subscriber PTZ_R_Auto_sub = nh.subscribe<robot_msgs::PTZ_perception>("/PTZ_R/PTZ_perception",1,PTZ_R_Auto);   

    // 发送数据
    Robot_L_ctrl_pub = nh.advertise<robot_msgs::robot_ctrl>("/robot_left_gimble_ctrl",1);
    Robot_R_ctrl_pub = nh.advertise<robot_msgs::robot_ctrl>("/robot_right_gimble_ctrl",1);
    Robot_main_yaw_pub = nh.advertise<std_msgs::Float32>("/robot_main_ctrl",1);

    // 建立需要订阅的消息对应的订阅器 (可能还得添加一个模式的同步)
    message_filters::Subscriber<robot_msgs::PTZ_perception> PTZ_L_sub(nh, "/PTZ_L/PTZ_perception", 1);  
    message_filters::Subscriber<robot_msgs::PTZ_perception> PTZ_R_sub(nh, "/PTZ_R/PTZ_perception", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<robot_msgs::PTZ_perception, robot_msgs::PTZ_perception> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), PTZ_L_sub, PTZ_R_sub);


    ROS_INFO("[Yaw_Communication_sync]: Start");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    // 初始化卡尔曼 | yaw & pitch
    kalman_yaw_L.Initial();
    kalman_pitch_L.Initial();
    kalman_yaw_R.Initial();
    kalman_pitch_R.Initial();
    kalman_yaw_main.Initial();

    Eigen::Matrix<double,2,1> x_k1_yaw_L;  // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> p_x_k_yaw_L; // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> x_k1_pitch_L;  // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> p_x_k_pitch_L; // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> x_k1_yaw_R;  // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> p_x_k_yaw_R; // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> x_k1_pitch_R;  // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> p_x_k_pitch_R; // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> x_k1_yaw_main;  // k-1时刻的滤波值，即是k-1时刻的值
    Eigen::Matrix<double,2,1> p_x_k_yaw_main; // k-1时刻的滤波值，即是k-1时刻的值

    // 创建发送数据
    robot_msgs::robot_ctrl Robot_L_ctrl_t;
    robot_msgs::robot_ctrl Robot_R_ctrl_t;
    std_msgs::Float32 Robot_main_yaw_t;
    // 60Hz的频率 | 加入卡尔曼滤波 | 60HZ 0.016s
    int HZ = 80;    // 赫兹HZ
    ros::Rate loop_rate(HZ);
    while (ros::ok())
    {   
        // 设置卡尔曼时间
        float time = 1/HZ;
        kalman_yaw_L.setF(time);
        kalman_pitch_L.setF(time);
        kalman_yaw_R.setF(time);
        kalman_pitch_R.setF(time);
        kalman_yaw_main.setF(time);

        // 使用预测步还是跟新步? | 待测试,目前预测步
        /** 预测步 */
        p_x_k_yaw_L = kalman_yaw_L.predict();
        p_x_k_pitch_L = kalman_pitch_L.predict();
        p_x_k_yaw_R = kalman_yaw_R.predict();
        p_x_k_pitch_R = kalman_pitch_R.predict();
        p_x_k_yaw_main = kalman_yaw_main.predict();

        /** 更新步 */
        x_k1_yaw_L = kalman_yaw_L.update(Decision_Yaw_L);
        x_k1_pitch_L = kalman_pitch_L.update(Decision_pitch_L);
        x_k1_yaw_R = kalman_yaw_R.update(Decision_Yaw_R);
        x_k1_pitch_R = kalman_pitch_R.update(Decision_pitch_R);
        x_k1_yaw_main = kalman_yaw_main.update(Decision_Yaw_count);

        //大Yaw轴数据
        // Robot_main_yaw_t.data = Decision_Yaw_count;
        Robot_main_yaw_t.data = p_x_k_yaw_main[0];

        //左右开火命令
        Robot_L_ctrl_t.fire_command = Decision_fire_command_L;
        Robot_R_ctrl_t.fire_command = Decision_fire_command_R;
        // 左右开火模式
        Robot_L_ctrl_t.fire_mode = Decision_fire_mode_L;
        Robot_R_ctrl_t.fire_mode = Decision_fire_mode_R;
        // // 左右yaw轴数据
        // Robot_L_ctrl_t.yaw = Decision_Yaw_L;
        // Robot_R_ctrl_t.yaw = Decision_Yaw_R;
        // // 左右pitch轴数据
        // Robot_L_ctrl_t.pitch = Decision_pitch_L;
        // Robot_R_ctrl_t.pitch = Decision_pitch_R;

        Robot_L_ctrl_t.yaw = p_x_k_yaw_L[0];
        Robot_R_ctrl_t.yaw = p_x_k_yaw_R[0];
        // 左右pitch轴数据
        Robot_L_ctrl_t.pitch = p_x_k_pitch_L[0];
        Robot_R_ctrl_t.pitch = p_x_k_pitch_R[0];
        // 左右跟踪情况
        Robot_L_ctrl_t.is_follow = Decision_target_lock_L;
        Robot_R_ctrl_t.is_follow = Decision_target_lock_R;
        
        Robot_L_ctrl_pub.publish(Robot_L_ctrl_t);
        Robot_R_ctrl_pub.publish(Robot_R_ctrl_t);
        Robot_main_yaw_pub.publish(Robot_main_yaw_t);

        loop_rate.sleep();
        ros::spinOnce();
    }
    

    ros::spin();

    return 0;

}
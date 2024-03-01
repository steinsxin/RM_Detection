#include "ros/ros.h"
#include <ros/time.h>

// msg
#include "robot_msg/Robot_ctrl.h"
#include "robot_msg/PTZ_Yaw.h"

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

// 计算yaw轴数据,进行控制处理
void callback(const robot_msg::Robot_ctrlConstPtr &PTZ_L, const robot_msg::Robot_ctrlConstPtr &PTZ_R, const robot_msg::PTZ_YawConstPtr &PTZ_Yaw){

    // 0x31表示跟踪,0x32表示丢失
    int target_lock_L = PTZ_L->target_lock;
    int target_lock_R = PTZ_R->target_lock;

    bool Mode;  // 模式处理
    bool situation_1 = (target_lock_L == 0x31) && (target_lock_R == 0x31);  // 情况1
    bool situation_2 = (target_lock_L == 0x31) && (target_lock_R == 0x32);  // 情况2
    bool situation_3 = (target_lock_L == 0x32) && (target_lock_R == 0x31);  // 情况3

    // 计算大云台Yaw轴移动角度
    float Yaw_count;
    if(situation_1){
        Yaw_count = (PTZ_L->yaw + PTZ_R->yaw) / 2.0f;
    }
    else if(situation_2){
        Yaw_count = (PTZ_L->yaw);
    }
    else if(situation_3){
        Yaw_count = (PTZ_R->yaw);
    }
    
    // 计算两个小云台yaw轴移动角度(相对于大云台的yaw轴角度)
    float Yaw_L;
    float Yaw_R;
    Yaw_L = PTZ_L->yaw - PTZ_Yaw->yaw;
    Yaw_R = PTZ_R->yaw - PTZ_Yaw->yaw;

    // 差决策部分,击打同一目标则比对两个装甲板分数,不同目标则已经通过云台|全向感知融合节点进行修正

    // 发送数据部分
    
}

// 同步左右云台的yaw轴数据和大云台的yaw轴数据,进行数据处理
int main(int argc, char *argv[]){

    // 设置语言运行环境
    setlocale(LC_ALL,"");  

    // 初始化节点
    ros::init(argc, argv, "Yaw_Communication_sync");

    // 创建句柄
    ros::NodeHandle nh;
    
    // 建立需要订阅的消息对应的订阅器 (可能还得添加一个模式的同步)
    message_filters::Subscriber<robot_msg::Robot_ctrl> PTZ_L_sub(nh, "/PTZ_L/PTZ_perception", 1);  
    message_filters::Subscriber<robot_msg::Robot_ctrl> PTZ_R_sub(nh, "/PTZ_R/PTZ_perception", 1);  
    message_filters::Subscriber<robot_msg::PTZ_Yaw> PTZ_YAW_sub(nh, "/PTZ_Yaw_data", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<robot_msg::Robot_ctrl, robot_msg::Robot_ctrl,robot_msg::PTZ_Yaw> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), PTZ_L_sub, PTZ_R_sub, PTZ_YAW_sub);

    ROS_INFO("--Yaw_Communication_sync Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2, _3));

    ros::spin();

    return 0;

}
#include "ros/ros.h"
#include <ros/time.h>

// msg
#include "robot_msg/omni_perception.h"
#include "robot_msg/PTZ_perception.h"
#include "robot_msg/Robot_ctrl.h"

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>


ros::Publisher Decision_pub;

void callback(const robot_msg::omni_perceptionConstPtr &omni_L, const robot_msg::PTZ_perceptionConstPtr &PTZ_L){

    float Decision_pitch;           // 决策pitch
    float Decision_yaw;             // 决策yaw
    float Decision_fire_command;    // 决策开火
    float Decision_fire_mode;       // 决策开火模式[连发|三连发]

    // ptich轴数据只使用云台数据
    Decision_pitch = PTZ_L->pitch;
    Decision_fire_command = PTZ_L->fire_command;

    // 判断云台|全向跟踪模式
    if(PTZ_L->target_lock == 0x31){
        // 判断分数进行决策(Yaw轴数据)
        if(PTZ_L->score >= omni_L->score){
            // 选择云台
            Decision_yaw = PTZ_L->yaw;
        }else{
            // 选择全向感知
            Decision_yaw = omni_L->yaw;
        }
    }
    else{
        Decision_yaw = omni_L->yaw;
    }

    // 创建发送数据
    robot_msg::PTZ_perception PTZ_Yaw_t;
    
    // 填充数据
    PTZ_Yaw_t.header.frame_id = "PTZ_Yaw_L";
    PTZ_Yaw_t.header.seq++;
    PTZ_Yaw_t.header.stamp = ros::Time::now();

    PTZ_Yaw_t.pitch = Decision_pitch;                   // pitch轴
    PTZ_Yaw_t.yaw = Decision_yaw;                       // yaw轴
    PTZ_Yaw_t.fire_command = Decision_fire_command;     // 开火指令
    PTZ_Yaw_t.fire_mode = Decision_fire_mode;           // 开火模式

    // 发送数据
    Decision_pub.publish(PTZ_Yaw_t);
}

int main(int argc, char *argv[]){

    // 设置语言运行环境
    setlocale(LC_ALL,"");  

    // 初始化节点
    ros::init(argc, argv, "PTZ_perception_L");

    // 创建句柄
    ros::NodeHandle nh;

    Decision_pub = nh.advertise<robot_msg::Robot_ctrl>("/PTZ_L/PTZ_perception",1);

    // 同步左云台|全向感知锁定信息,进行分数比较决策(可能还得添加一个模式的同步)
    message_filters::Subscriber<robot_msg::omni_perception> omni_L_sub(nh, "/omno_perception_L", 1);  
    message_filters::Subscriber<robot_msg::PTZ_perception> PTZ_L_sub(nh, "/PTZ_perception_L", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<robot_msg::omni_perception, robot_msg::PTZ_perception> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), omni_L_sub, PTZ_L_sub);

    ROS_INFO("--PTZ_perception_L Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

}
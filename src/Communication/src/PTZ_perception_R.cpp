#include "ros/ros.h"
#include <ros/time.h>

// msg
#include "robot_msg/omni_perception.h"
#include "robot_msg/PTZ_perception.h"

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

void callback(const robot_msg::omni_perceptionConstPtr &omni_R, const robot_msg::PTZ_perceptionConstPtr &PTZ_R){

    

}

int main(int argc, char *argv[]){

    // 设置语言运行环境
    setlocale(LC_ALL,"");  

    // 初始化节点
    ros::init(argc, argv, "PTZ_perception_R");

    // 创建句柄
    ros::NodeHandle nh;

    // 同步左云台|全向感知锁定信息,进行分数比较决策(可能还得添加一个模式的同步)
    message_filters::Subscriber<robot_msg::omni_perception> omni_R_sub(nh, "/omno_perception_R", 1);  
    message_filters::Subscriber<robot_msg::PTZ_perception> PTZ_R_sub(nh, "/PTZ_perception_L", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<robot_msg::omni_perception, robot_msg::PTZ_perception> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), omni_R_sub, PTZ_R_sub);

    ROS_INFO("--PTZ_perception_R Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

}
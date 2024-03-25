#include "ros/ros.h"
#include <ros/time.h>

// 结构体
#include "robot_status.h"

// msg
#include "robot_msgs/barrel.h"
#include "robot_msgs/PTZ_perception.h"
#include "robot_msgs/Track_reset.h"

// 消息过滤器
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>


ros::Publisher Decision_pub;
ros::Publisher Track_reset_pub;
static int lose_num = 0; 

// 全向感知和自瞄的切换方案
// 目前问题在于两个回调函数会有同时发送数据的情况,现在需要在全向感知开启的情况下
// 将自瞄发送数据给断开,目前想法是在接受到全向的数据时将标识符设置为1,表示开启全向感知,同时设置ROS时间戳
// 在自瞄下进行时间戳的判断,如果在一段时间内并未更新时间戳,则将标识符设置为0,判断全向感知离线
// 双头自瞄也需要进行这个判断,避免1个电脑离线的情况下双头无法自瞄

void Auto(const robot_msgs::PTZ_perceptionConstPtr &PTZ){

    float Decision_pitch;           // 决策pitch
    float Decision_yaw;             // 决策yaw
    float Decision_score;           // 决策开火
    float Decision_fire_command;    // 决策开火
    float Decision_fire_mode;       // 决策开火模式[连发|三连发]

    // 只使用云台数据
    Decision_pitch = PTZ->pitch;
    Decision_yaw = PTZ->yaw;        
    Decision_fire_command = PTZ->fire_command;
    Decision_fire_mode = PTZ->fire_mode;
    Decision_score = PTZ->score;


    // 创建发送数据
    robot_msgs::PTZ_perception PTZ_Yaw_t;
    
    //! 还需要判断跟踪状态
    // 填充数据
    PTZ_Yaw_t.header.frame_id = "PTZ_Yaw_L";
    PTZ_Yaw_t.header.seq++;
    PTZ_Yaw_t.header.stamp = ros::Time::now();

    PTZ_Yaw_t.pitch = Decision_pitch;                   // pitch轴
    PTZ_Yaw_t.yaw = Decision_yaw;                       // yaw轴
    PTZ_Yaw_t.track_id = PTZ->track_id;                 // 跟踪装甲板ID
    PTZ_Yaw_t.target_lock = PTZ->target_lock;           // 跟踪模式
    PTZ_Yaw_t.score = Decision_score;                   // 装甲板分数
    PTZ_Yaw_t.fire_command = Decision_fire_command;     // 开火指令
    PTZ_Yaw_t.fire_mode = Decision_fire_mode;           // 开火模式

    // 发送数据
    Decision_pub.publish(PTZ_Yaw_t);
}

void callback(const robot_msgs::barrelConstPtr &omni, const robot_msgs::PTZ_perceptionConstPtr &PTZ){

    float Decision_pitch;           // 决策pitch
    float Decision_yaw;             // 决策yaw
    float Decision_score;           // 决策开火
    float Decision_fire_command;    // 决策开火
    float Decision_fire_mode;       // 决策开火模式[连发|三连发]

    // ptich轴数据只使用云台数据
    Decision_pitch = PTZ->pitch;
    Decision_fire_command = PTZ->fire_command;
    Decision_fire_mode = PTZ->fire_mode;


    // 判断云台|全向跟踪模式
    if(PTZ->target_lock == 0x31 && omni->num == 1){
        // 根据ID和分数决定进行决策处理

        // ID判断是否为同一目标
        if(PTZ->track_id == omni->id){
            Decision_yaw = PTZ->yaw;
            Decision_score = PTZ->score;
            lose_num = 0;
        }
        else {
            // 根据分数进行丢失处理,达到一定阈值进行跟踪重置
            if(PTZ->score >= omni->grade){
                // 选择云台
                Decision_yaw = PTZ->yaw;
                Decision_score = PTZ->score;
            }else{
                // 丢失分数叠加,超出一定阈值重新进入跟踪模式
                lose_num++;
            }
        }
     
    }
    else{
        lose_num = 0;
        // 分数决策
        if(PTZ->score >= omni->grade){
            // 选择云台
            Decision_yaw = PTZ->yaw;
            Decision_score = PTZ->score;
        }else{
            // 选择全向感知
            Decision_yaw = omni->yaw;
            Decision_score = omni->grade;
        }
    }

    // 陀螺状态下选择相信云台
    if(PTZ->spin_state != UNKNOWN){
        Decision_yaw = PTZ->yaw;
        Decision_score = PTZ->score;
    }

    // 创建发送数据
    robot_msgs::PTZ_perception PTZ_Yaw_t;
    
    //! 还需要判断跟踪状态
    // 填充数据
    PTZ_Yaw_t.header.frame_id = "PTZ_Yaw_L";
    PTZ_Yaw_t.header.seq++;
    PTZ_Yaw_t.header.stamp = ros::Time::now();

    PTZ_Yaw_t.pitch = Decision_pitch;                   // pitch轴
    PTZ_Yaw_t.yaw = Decision_yaw;                       // yaw轴
    PTZ_Yaw_t.track_id = PTZ->track_id;               // 跟踪装甲板ID
    PTZ_Yaw_t.target_lock = PTZ->target_lock;         // 跟踪模式
    PTZ_Yaw_t.score = Decision_score;                   // 装甲板分数
    PTZ_Yaw_t.fire_command = Decision_fire_command;     // 开火指令
    PTZ_Yaw_t.fire_mode = Decision_fire_mode;           // 开火模式

    // 发送数据
    Decision_pub.publish(PTZ_Yaw_t);

    // 丢失阈值判断
    if(lose_num == 5){
        robot_msgs::Track_reset Track_reset_t;
        
        // 填充数据
        Track_reset_t.header.frame_id = "Track_reset_L";
        Track_reset_t.header.seq++;
        Track_reset_t.header.stamp = ros::Time::now();
        
        // 更新跟踪ID
        Track_reset_t.Track_id = omni->id;
        Track_reset_t.Reset = 1;

        // 发送跟踪重置指令
        Track_reset_pub.publish(Track_reset_t);
        lose_num = 0;
    }


}

// #define omni_mode       // 全向感知开关
int main(int argc, char *argv[]){

    // 设置语言运行环境
    setlocale(LC_ALL,"");  

    // 初始化节点
    ros::init(argc, argv, "PTZ_perception_L");

    // 创建句柄
    ros::NodeHandle nh;

    Decision_pub = nh.advertise<robot_msgs::PTZ_perception>("/PTZ_L/PTZ_perception",1);
    Track_reset_pub = nh.advertise<robot_msgs::Track_reset>("/PTZ_L/Track_Reset",1);    
#ifdef omni_mode
    // 同步左云台|全向感知锁定信息,进行分数比较决策(可能还得添加一个模式的同步)
    message_filters::Subscriber<robot_msgs::barrel> omni_L_sub(nh, "/Robot_left_imu", 1);  
    message_filters::Subscriber<robot_msgs::PTZ_perception> PTZ_L_sub(nh, "/PTZ_perception_L", 1);  

    // 同步ROS消息
    typedef message_filters::sync_policies::ApproximateTime<robot_msgs::barrel, robot_msgs::PTZ_perception> MySyncPolicy;

    // 创建同步器对象
    message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), omni_L_sub, PTZ_L_sub);

    ROS_INFO("--PTZ_perception_L Start--");
    // 注册同步回调函数
    sync.registerCallback(boost::bind(&callback, _1, _2));
#else
    // 创建订阅对象
    ros::Subscriber auto_pub = nh.subscribe<robot_msgs::PTZ_perception>("/PTZ_perception_L",1,Auto);   

#endif //omni_mode


    ros::spin();

}
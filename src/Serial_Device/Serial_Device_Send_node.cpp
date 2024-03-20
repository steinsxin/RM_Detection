//
// Created by steins_xin on 23-10-31.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "serial_main.h"
#include "ros/ros.h"
// 外部头文件
#include "robot_status.h"
#include "robot_struct.h"
// msg
#include "robot_msg/Vision.h"

int main(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    // 初始化 ROS 节点
    ros::init(argc,argv,"Vision_pub");

    // 创建 ROS 句柄
    ros::NodeHandle nh;

    // 创建发布者对象
    ros::Publisher pub = nh.advertise<robot_msg::Vision>("Vision_data",10);

    // 创建发送数据
    robot_msg::Vision vision_t;

    bool Get_data;
    SerialMain serial;  // usb
    ROS_INFO("---Vision_pub Start---");
    while (ros::ok()){
        Get_data = serial.ReceiverMain();                                          // usb
        if(Get_data){

            // 填充数据
            vision_t.header.frame_id = "vision";
            vision_t.header.seq++;
            vision_t.header.stamp = ros::Time::now();
            vision_t.id = serial.vision_msg_.id;
            vision_t.mode = serial.vision_msg_.mode;
            vision_t.pitch = serial.vision_msg_.pitch;
            vision_t.yaw = serial.vision_msg_.yaw;
            vision_t.roll = serial.vision_msg_.roll;

            //! 注意:自定义数组resize设置大小,不然会出现数据错误的情况 
            vision_t.quaternion.resize(4);
            for (int i = 0; i < 4; i++)
            {
                vision_t.quaternion[i] = serial.vision_msg_.quaternion[i];
            }
            vision_t.shoot = serial.vision_msg_.shoot;

            // 发送数据
            pub.publish(vision_t);
        }
        ros::spinOnce();
    }
}
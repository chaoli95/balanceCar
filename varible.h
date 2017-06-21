/*
 * varible.h
 *
 *  Created on: 2017年6月20日
 *      Author: lchao
 */

#ifndef VARIBLE_H_
#define VARIBLE_H_

typedef unsigned char   u8;
typedef unsigned int   u16;
typedef unsigned long  u32;

extern u8 Way_Angle;                                      //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波
extern int Encoder_Left,Encoder_Right;                     //左右编码器的脉冲计数
extern int Moto1,Moto2;                                     //电机PWM变量 应是motor的 向moto致敬
extern u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu; //蓝牙遥控相关的变量
extern u8 Flag_Stop,Flag_Show;                               //停止标志位和 显示标志位 默认停止 显示打开
extern int Voltage,Voltage_Zheng,Voltage_Xiao;                //电池电压采样相关的变量
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;           //平衡倾角 平衡陀螺仪 转向陀螺仪
extern float Show_Data_Mb;                                    //全局显示变量，用于显示需要查看的数据
extern int Temperature;
extern u32 Distance;                                           //超声波测距
extern u8 Bi_zhang,delay_50,delay_flag,PID_Send,Flash_Send;
extern float Acceleration_Z;
extern float Balance_Kp,Balance_Kd,Velocity_Kp,Velocity_Ki;
extern u16 PID_Parameter[10],Flash_Parameter[10];


#endif /* VARIBLE_H_ */

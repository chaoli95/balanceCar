/*
 * varible.h
 *
 *  Created on: 2017��6��20��
 *      Author: lchao
 */

#ifndef VARIBLE_H_
#define VARIBLE_H_

typedef unsigned char   u8;
typedef unsigned int   u16;
typedef unsigned long  u32;

extern u8 Way_Angle;                                      //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲�
extern int Encoder_Left,Encoder_Right;                     //���ұ��������������
extern int Moto1,Moto2;                                     //���PWM���� Ӧ��motor�� ��moto�¾�
extern u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu; //����ң����صı���
extern u8 Flag_Stop,Flag_Show;                               //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
extern int Voltage,Voltage_Zheng,Voltage_Xiao;                //��ص�ѹ������صı���
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;           //ƽ����� ƽ�������� ת��������
extern float Show_Data_Mb;                                    //ȫ����ʾ������������ʾ��Ҫ�鿴������
extern int Temperature;
extern u32 Distance;                                           //���������
extern u8 Bi_zhang,delay_50,delay_flag,PID_Send,Flash_Send;
extern float Acceleration_Z;
extern float Balance_Kp,Balance_Kd,Velocity_Kp,Velocity_Ki;
extern u16 PID_Parameter[10],Flash_Parameter[10];


#endif /* VARIBLE_H_ */

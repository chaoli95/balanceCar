/*
 * control.h
 *
 *  Created on: 2017Äê6ÔÂ18ÈÕ
 *      Author: lchao
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#define	PI		3.14159265358979323846	/* pi */
#define ZHONGZHI 3
#define DIFFERENCE 100

extern volatile int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
int EXTI15_10_IRQHandler(void);
int balance(float angle,float gyro);
int velocity(int encoder_left,int encoder_right);
int turn(int encoder_left,int encoder_right,float gyro);
void Set_Pwm(int moto1,int moto2);
void Key(void);
void Xianfu_Pwm(void);
unsigned char Turn_Off(float angle, int voltage);
int myabs(int a);
int Pick_Up(float Acceleration,float Angle,int encoder_left,int encoder_right);
int Put_Down(float Angle,int encoder_left,int encoder_right);
void getAngle(void);


#endif /* CONTROL_H_ */

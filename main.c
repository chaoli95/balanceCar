#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "MPU9150.h"
#include "I2C.h"
#include "control.h"
#include "filter.h"
#include "varible.h"
#include "motor.h"


u8 Way_Angle=2;                             //»ñÈ¡½Ç¶ÈµÄËã·¨£¬1£ºËÄÔªÊý  2£º¿¨¶ûÂü  3£º»¥²¹ÂË²¨
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //À¶ÑÀÒ£¿ØÏà¹ØµÄ±äÁ¿
u8 Flag_Stop=1,Flag_Show=0;                 //Í£Ö¹±êÖ¾Î»ºÍ ÏÔÊ¾±êÖ¾Î» Ä¬ÈÏÍ£Ö¹ ÏÔÊ¾´ò¿ª
int Encoder_Left,Encoder_Right;             //×óÓÒ±àÂëÆ÷µÄÂö³å¼ÆÊý
int Moto1,Moto2;                            //µç»úPWM±äÁ¿ Ó¦ÊÇMotorµÄ ÏòMotoÖÂ¾´
int Temperature;                            //ÏÔÊ¾ÎÂ¶È
int Voltage;                                //µç³ØµçÑ¹²ÉÑùÏà¹ØµÄ±äÁ¿
float Angle_Balance,Gyro_Balance,Gyro_Turn; //Æ½ºâÇã½Ç Æ½ºâÍÓÂÝÒÇ ×ªÏòÍÓÂÝÒÇ
float Show_Data_Mb;                         //È«¾ÖÏÔÊ¾±äÁ¿£¬ÓÃÓÚÏÔÊ¾ÐèÒª²é¿´µÄÊý¾Ý
u32 Distance;                               //³¬Éù²¨²â¾à
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;  //ÑÓÊ±ºÍµ÷²ÎµÈ±äÁ¿
float Acceleration_Z;                       //ZÖá¼ÓËÙ¶È¼Æ
float Balance_Kp=300,Balance_Kd=1,Velocity_Kp=80,Velocity_Ki=0.4;//PID²ÎÊý
u16 PID_Parameter[10],Flash_Parameter[10];  //FlashÏà¹ØÊý×é

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	motorInit();
	clearI2CPort();
	initI2C();
	initMPU9150();
	P8DIR |= BIT1+BIT2;
	P1DIR |= BIT0 + BIT1;
	P8OUT |= BIT1+BIT2;
	P1DIR |= BIT0+BIT1;

	int i;
	while(1)
	{
//		getAngle();
//		Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
//		Moto1=Balance_Pwm;
//		Moto2=Balance_Pwm;
//		Xianfu_Pwm();
//		if(angle > 0) P8OUT |= BIT2;
//		else P8OUT &= ~BIT2;
//		setPwm(Moto1/72,Moto2/72);
	}
}


/*
 * control.c
 *
 *  Created on: 2017年6月18日
 *      Author: lchao
 */

#include "control.h"
#include "filter.h"
#include "MPU9150.h"
#include <math.h>
#include "varible.h"
#include "motor.h"
#include <stdio.h>
#include <msp430.h>
#include "I2C.h"

volatile int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
volatile float accel[3]={0};
volatile float gyro[3]={0};

u8 Flag_Target;
u32 Flash_R_Count;
int Voltage_Temp,Voltage_Count,Voltage_All;


static unsigned char txData[] =              // Table of data to transmit
{0,0,0};

//char temp[20] = {0};

//#pragma vector=PORT2_VECTOR
//__interrupt
//void Port_2(void)
//{
//	P2IE &= ~BIT4;
//	switch(P2IFG)
//	{
//	case BIT4:
//		P8OUT ^= BIT1;
//		getAngle();
//		Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
//		Moto1=Balance_Pwm;
//		Moto2=Balance_Pwm;
//		Xianfu_Pwm();
//		if(angle > 0) P8OUT |= BIT2;
//		else P8OUT &= ~BIT2;
//		if(angle > - 15 && angle < 15)
//		{
//			int a = (int)angle;
//			P1OUT &= ~(BIT1+BIT2+BIT3+BIT4);
//			P1OUT |= a << 1;
//		}
//	    setPwm(Moto1/72,Moto2/72);
//		break;
//	default:
//		break;
//	}
//	P2IFG &= 0x0;
//	P2IE |= BIT4;
//}

int balance(float Angle,float Gyro)
{
	float Bias;
	int balance;
	Bias=Angle-ZHONGZHI;       //===Çó³öÆ½ºâµÄ½Ç¶ÈÖÐÖµ ºÍ»úÐµÏà¹Ø

	balance=Balance_Kp*Bias+Gyro*Balance_Kd;   //===¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊý kdÊÇDÏµÊý
	__no_operation();
	return balance;
}

int velocity(int encoder_left,int encoder_right)
{
	static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral,Target_Velocity;
	//=============Ò£¿ØÇ°½øºóÍË²¿·Ö=======================//
//	if(Bi_zhang==1&&Flag_sudu==1)  Target_Velocity=45;                 //Èç¹û½øÈë±ÜÕÏÄ£Ê½,×Ô¶¯½øÈëµÍËÙÄ£Ê½
//    else 	                         Target_Velocity=110;
//	if(1==Flag_Qian)    	Movement=Target_Velocity/Flag_sudu;	         //===Ç°½ø±êÖ¾Î»ÖÃ1
//	else if(1==Flag_Hou)	Movement=-Target_Velocity/Flag_sudu;         //===ºóÍË±êÖ¾Î»ÖÃ1
//	else  Movement=0;
//	if(Bi_zhang==1&&Distance<500&&Flag_Left!=1&&Flag_Right!=1)        //±ÜÕÏ±êÖ¾Î»ÖÃ1ÇÒ·ÇÒ£¿Ø×ªÍäµÄÊ±ºò£¬½øÈë±ÜÕÏÄ£Ê½
//		Movement=-Target_Velocity/Flag_sudu;
   //=============ËÙ¶ÈPI¿ØÖÆÆ÷=======================//
	Encoder_Least =(Encoder_Left+Encoder_Right)-0;                    //===»ñÈ¡×îÐÂËÙ¶ÈÆ«²î==²âÁ¿ËÙ¶È£¨×óÓÒ±àÂëÆ÷Ö®ºÍ£©-Ä¿±êËÙ¶È£¨´Ë´¦ÎªÁã£©
	Encoder *= 0.8;		                                                //===Ò»½×µÍÍ¨ÂË²¨Æ÷
	Encoder += Encoder_Least*0.2;	                                    //===Ò»½×µÍÍ¨ÂË²¨Æ÷
	Encoder_Integral +=Encoder;                                       //===»ý·Ö³öÎ»ÒÆ »ý·ÖÊ±¼ä£º10ms
	Encoder_Integral=Encoder_Integral-Movement;                       //===½ÓÊÕÒ£¿ØÆ÷Êý¾Ý£¬¿ØÖÆÇ°½øºóÍË
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===»ý·ÖÏÞ·ù
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===»ý·ÖÏÞ·ù
	Velocity=Encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;                          //===ËÙ¶È¿ØÖÆ
//	if(Turn_Off(Angle_Balance,Voltage)==1||Flag_Stop==1)   Encoder_Integral=0;      //===µç»ú¹Ø±ÕºóÇå³ý»ý·Ö
	return Velocity;
}

void Xianfu_Pwm(void)
{
	int Amplitude=6900;    //===PWMÂú·ùÊÇ7200 ÏÞÖÆÔÚ6900
//	if(Flag_Qian==1)  Moto1-=DIFFERENCE;  //DIFFERENCEÊÇÒ»¸öºâÁ¿Æ½ºâÐ¡³µµç»úºÍ»úÐµ°²×°²îÒìµÄÒ»¸ö±äÁ¿¡£Ö±½Ó×÷ÓÃÓÚÊä³ö£¬ÈÃÐ¡³µ¾ßÓÐ¸üºÃµÄÒ»ÖÂÐÔ¡£
//	if(Flag_Hou==1)   Moto2+=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;
    if(Moto1>Amplitude)  Moto1=Amplitude;
    if(Moto2<-Amplitude) Moto2=-Amplitude;
    if(Moto2>Amplitude)  Moto2=Amplitude;

}

void getAngle(void)
{
	unsigned char buf[6];
//	MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
	txData[0]=MPU6050_GYRO_OUT;
	sendI2C(txData,1,NO_STOP);
	readI2CBytes(6,buf);
	gyro[0] = (buf[0] << 8) + buf[1];
	gyro[1] = (buf[2] << 8) + buf[3];
	gyro[2] = (buf[4] << 8) + buf[5];
//	MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
	txData[0]=MPU6050_ACC_OUT;
	sendI2C(txData,1,NO_STOP);
	readI2CBytes(6,buf);
	accel[0] = (buf[0] << 8) + buf[1];
	accel[1] = (buf[2] << 8) + buf[3];
	accel[2] = (buf[4] << 8) + buf[5];
   	//readMPU6050GyroFloat(gyro);
   	//readMPU6050AccFloat(accel);
	if(gyro[1]>32768)  gyro[1]-=65536;
	if(gyro[2]>32768)  gyro[2]-=65536;
	if(accel[0]>32768) accel[0]-=65536;
	if(accel[2]>32768) accel[2]-=65536;
	Gyro_Balance=-gyro[1];
	accel[1]=atan2(accel[0],accel[2])*180/PI;
	gyro[1]=gyro[1]/16.4;
	Yijielvbo(accel[1],-gyro[1]);
	Angle_Balance=angle;                                   //¸üÐÂÆ½ºâÇã½Ç
	Gyro_Turn=gyro[2];                                      //¸üÐÂ×ªÏò½ÇËÙ¶È
	Acceleration_Z=accel[2];
}



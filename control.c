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
#include "MSP-EXP430F5529_HAL/HAL_Board.h"
#include "MSP-EXP430F5529_HAL/HAL_Dogs102x6.h"
#include "gpio.h"
#include "varible.h"
#include "motor.h"
#include <stdio.h>

int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
u8 Flag_Target;
u32 Flash_R_Count;
int Voltage_Temp,Voltage_Count,Voltage_All;


//char temp[20] = {0};

#pragma vector=PORT2_VECTOR
__interrupt
void Port_2(void)
{
	switch(P2IFG)
	{
	case BIT4:
		getAngle();
		//sprintf(temp,"angle:%d",(int)angle);
		//Dogs102x6_stringDraw(1,1,temp,0);
		Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
		Moto1=Balance_Pwm;
		Moto2=Balance_Pwm;
		Xianfu_Pwm();
		if(angle > 0) Board_ledOn(LED2);
		else Board_ledOff(LED2);
		if(Moto1 > 5000 || Moto1 < - 5000) Board_ledOn(LED3);
		else Board_ledOff(LED3);
		setPwm(Moto1/72,Moto2/72);
		break;
	default:
		break;
	}
	P2IFG &= ~BIT4;
}

int balance(float Angle,float Gyro)
{
	float Bias;
	int balance;
	Bias=Angle-ZHONGZHI;       //===Çó³öÆ½ºâµÄ½Ç¶ÈÖÐÖµ ºÍ»úÐµÏà¹Ø
	balance=Balance_Kp*Bias+Gyro*Balance_Kd;   //===¼ÆËãÆ½ºâ¿ØÖÆµÄµç»úPWM  PD¿ØÖÆ   kpÊÇPÏµÊý kdÊÇDÏµÊý
	return balance;
}

void Xianfu_Pwm(void)
{
	int Amplitude=5000;    //===PWMÂú·ùÊÇ7200 ÏÞÖÆÔÚ6900
//	if(Flag_Qian==1)  Moto1-=DIFFERENCE;  //DIFFERENCEÊÇÒ»¸öºâÁ¿Æ½ºâÐ¡³µµç»úºÍ»úÐµ°²×°²îÒìµÄÒ»¸ö±äÁ¿¡£Ö±½Ó×÷ÓÃÓÚÊä³ö£¬ÈÃÐ¡³µ¾ßÓÐ¸üºÃµÄÒ»ÖÂÐÔ¡£
//	if(Flag_Hou==1)   Moto2+=DIFFERENCE;
    if(Moto1<-Amplitude) Moto1=-Amplitude;
    if(Moto1>Amplitude)  Moto1=Amplitude;
    if(Moto2<-Amplitude) Moto2=-Amplitude;
    if(Moto2>Amplitude)  Moto2=Amplitude;

}

void getAngle(void)
{
	float accel[3]={0};
	float gyro[3]={0};
   	readMPU6050GyroFloat(gyro);
   	readMPU6050AccFloat(accel);
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



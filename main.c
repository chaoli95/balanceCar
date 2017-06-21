#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "MSP-EXP430F5529_HAL/HAL_Dogs102x6.h"
#include "MSP-EXP430F5529_HAL/HAL_Board.h"
#include "MSP-EXP430F5529_HAL/HAL_Wheel.h"
//#include "MSP-EXP430F5529_HAL/HAL_Buttons.h"
#include "MPU9150.h"
#include "I2C.h"
#include "control.h"
#include "filter.h"
#include "driverlib.h"
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


char temp[20] = {0};
void configureInterruptSource(void)
{
	P2IE |=  BIT4;                            // P1.3 interrupt enabled
	P2IES |= BIT4;                            // P1.3 Hi/lo edge
	P2REN |= BIT4;                            // Enable Pull Up on SW2 (P1.3)
	P2IFG &= ~BIT4;
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	uint8_t contrast = 11;            //读取FLASH中对比度值
	uint8_t brightness = 11;        //读取FLASH中背光值

	Board_init();
	Dogs102x6_init();
	Dogs102x6_setBacklight(contrast);          //设置初始背光值
	Dogs102x6_setContrast(brightness);             //设置初始对比度值
	Dogs102x6_clearScreen();                     //清屏
	Wheel_init();
	motorInit();
	configureInterruptSource();
	clearI2CPort();
	initI2C();
	initMPU9150();
	//Board_ledOff(LED_ALL);
	while(1)
	{
//		WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
//		if(Flash_Send==1)        //Ð´ÈëPID²ÎÊýµ½Flash,ÓÉapp¿ØÖÆ¸ÃÖ¸Áî
//		{
//          	Flash_Write();
//          	Flash_Send=0;
//		}
//		if(Flag_Show==0)          //Ê¹ÓÃMiniBalance APPºÍOLEDÏÔÊ¾ÆÁ
//		{
//			APP_Show();
//			oled_show();            //===ÏÔÊ¾ÆÁ´ò¿ª
//			}
//		else                      //Ê¹ÓÃMiniBalanceÉÏÎ»»ú ÉÏÎ»»úÊ¹ÓÃµÄÊ±ºòÐèÒªÑÏ¸ñµÄÊ±Ðò£¬¹Ê´ËÊ±¹Ø±Õapp¼à¿Ø²¿·ÖºÍOLEDÏÔÊ¾ÆÁ
//		{
//			DataScope();          //¿ªÆôMiniBalanceÉÏÎ»»ú
//		}
//		delay_flag=1;
//		delay_50=0;
//		while(delay_flag);	     //Í¨¹ýMPU6050µÄINTÖÐ¶ÏÊµÏÖµÄ5



//		getAngle();
//		//sprintf(temp,"angle:%d",(int)angle);
//		//Dogs102x6_stringDraw(1,1,temp,0);
//		Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
//		Moto1=Balance_Pwm;
//		Moto2=Balance_Pwm;
//		Xianfu_Pwm();
//		if(angle > 0) Board_ledOn(LED2);
//		else Board_ledOff(LED2);
//		if(Moto1 > 5000 || Moto1 < - 5000) Board_ledOn(LED3);
//		else Board_ledOff(LED3);
//		setPwm(Moto1/72,Moto2/72);
	}
}


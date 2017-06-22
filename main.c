#include <msp430.h>
//#include <stdio.h>
#include <stdlib.h>
#include "MPU9150.h"
#include "I2C.h"
#include "control.h"
#include "filter.h"
#include "varible.h"
#include "motor.h"

int Moto1,Moto2;
float Angle_Balance,Gyro_Balance,Gyro_Turn;
u8 delay_50,delay_flag;
float Acceleration_Z;
float Balance_Kp=300,Balance_Kd=1,Velocity_Kp=80,Velocity_Ki=0.4;



int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	volatile unsigned int i;
	for(i=50000;i>0;i--);
	P8DIR |= BIT1+BIT2;
	P8OUT |= BIT1+BIT2;

	P2REN |= BIT4;                            // Enable P1.4 internal resistance
	P2OUT |= BIT4;                            // Set P1.4 as pull-Up resistance
	P2IES &= ~BIT4;                           // P1.4 Lo/Hi edge
	P2IFG &= ~BIT4;                           // P1.4 IFG cleared
	P2IE |= BIT4;                             // P1.4 interrupt enabled


	clearI2CPort();
	initI2C();
	initMPU9150();
	motorInit();

//	P1DIR |= BIT1+BIT2+BIT3+BIT4;
//	P1OUT &= ~BIT1 + ~BIT3;


//	int flag = 0;
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


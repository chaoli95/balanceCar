///////////////////////////////////////////////////////////////////////////////


//             -----------------
//           -|             P2.4|<-------left a
//            |             P6.4|<-------left b
//           -|             P2.3|<-------right a
//            |             P6.6|<-------right b
//            |                 |
///////////////////////////////////////////////////////////////////////////////
#include <msp430.h>
//#include <stdio.h>
#include <stdlib.h>
#include "MPU9150.h"
#include "I2C.h"
#include "control.h"
#include "filter.h"
#include "varible.h"
#include "motor.h"

volatile int Moto1,Moto2;
volatile float Angle_Balance,Gyro_Balance,Gyro_Turn;
volatile u8 delay_50,delay_flag;
volatile float Acceleration_Z;
volatile float Balance_Kp=450 ,Balance_Kd=1.0,Velocity_Kp=-80,Velocity_Ki=-0.4;
volatile int Encoder_Left,Encoder_Right;
volatile u16 last;
volatile u16 now;
volatile u8 timer0Count; 	//wait for 0.1s
volatile int tempELeft, tempERight;

void clearEncoderCounter(void);

int main(void)
 {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	volatile unsigned int i;

	for(i=50000;i>0;i--);
	P8DIR |= BIT1+BIT2;
	P8OUT |= BIT1+BIT2;

	P1DIR |= BIT1+BIT2+BIT3+BIT4+BIT5;
	P1OUT &= ~(BIT1+BIT2+BIT3+BIT4+BIT5);

	P6DIR &= ~(BIT4 + BIT6);
	//P6SEL |= BIT4 + BIT6;

	P2SEL |= BIT3 + BIT4;

	TA2CCTL1 = CM_1+CCIS_0+SCS+CAP+CCIE;//p2.4
//	TA2CCTL0 = CM_1+CCIS_0+SCS+CAP+CCIE;//p2.3
	TA2CTL = TASSEL_2 + MC_2 + ID_1;

	TA0CCTL0 = CCIE;
	TA0CCR0 = 0xffff;
	TA0CTL = TASSEL_2 + MC_1 + TACLR;

	clearI2CPort();
	initI2C();
	initMPU9150();
	motorInit();

	while(1)
	{
		WDTCTL = WDTPW+WDTCNTCL;
		P8OUT ^= BIT1;
		getAngle();
		Balance_Pwm =balance(Angle_Balance,Gyro_Balance);
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Left);
		Moto1=Balance_Pwm-Velocity_Pwm;
		Moto2=Balance_Pwm-Velocity_Pwm;
		Xianfu_Pwm();
		if(Encoder_Left >= 0) P8OUT |= BIT1;
		else P8OUT &= ~BIT1;
		if(angle > - 15 && angle < 15)
		{
			int a = (int)angle;
			P1OUT &= ~(BIT1+BIT2+BIT3+BIT4);
			P1OUT |= a << 1;
		}
//		P1OUT &= ~(BIT1+BIT2+BIT3+BIT4+BIT5+BIT6);
//		if(Encoder_Left > -25 && Encoder_Left < 25)
//		{
//			P1OUT |= BIT1;
//		} else if (Encoder_Left > -45 && Encoder_Left < 45)
//		{
//			P1OUT |= BIT2;
//		} else if(Encoder_Left > -55 && Encoder_Left < 55)
//		{
//			P1OUT |= BIT3;
//		} else
//		{
//			P1OUT |= BIT4;
//		}
		__no_operation();
		setPwm(Moto1/72,Moto2/72);
//		setPwm(-5,-5);
	}
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2_ISR(void)
{

}

//#pragma vector=TIMER2_A0_VECTOR
//__interrupt void Timer2_A0_ISR(void)
//{
//	if(P6IN&BIT6)
//	{
//		++tempERight;
//		P8OUT |= BIT1;
//	} else
//	{
//		--tempERight;
//		P8OUT &= ~BIT1;
//	}
//}

#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
	P1OUT ^= BIT5;
	switch(__even_in_range(TA2IV,14))
	{
	case  0: break;                          // No interrupt
	case  2:
		if(P6IN & BIT4)
		{
			++tempELeft;
			P8OUT |= BIT2;
		} else
		{
			--tempELeft;
			P8OUT &= ~BIT2;
		}
		break;                          // CCR1 not used
	case  4: break;                          // CCR2 not used
	case  6: break;                          // reserved
	case  8: break;                          // reserved
	case 10: break;                          // reserved
	case 12: break;                          // reserved
	case 14:
		//P1OUT ^= BIT1;
		break;                          // overflow
	default: break;
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	__no_operation();

	Encoder_Left = tempELeft;
	Encoder_Right = tempERight;
	tempELeft = 0;
	tempERight = 0;
}


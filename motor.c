//#include "driverlib.h"
#include "motor.h"
#include <msp430.h>

#define u16 unsigned int
#define timer_period 100

void setPwm(int leftpwmin,int rightpwmin)
{
     //int dutycycle_left,dutycycle_right;

     if (leftpwmin>0)
     {
    	 P7OUT |= BIT1;
    	 P7OUT &= ~BIT2;
     }
     else{
    	 P7OUT |= BIT2;
    	 P7OUT &= ~BIT1;
     }
     if (rightpwmin>0)
     {
    	 P4OUT |= BIT4;
    	 P4OUT &= ~BIT0;
     }
     else{
    	 P4OUT |= BIT0;
    	 P4OUT &= ~BIT4;
     }
     //u16 a = (leftpwmin>0 ? leftpwmin : -leftpwmin)*timer_period/100;
     __no_operation();
     TBCCR3 = (u16)(leftpwmin>0 ? leftpwmin : -leftpwmin)*timer_period/100;
     TA1CCR2 = (u16)(rightpwmin>0 ? rightpwmin : -rightpwmin)*timer_period/100;
}

//int abs(int a){
//	if (a>=0)
//		return a;
//	else return (0-a);
//}

void motorInit(){

	P7DIR |= BIT1+BIT2+BIT3;
	P4DIR |= BIT0+BIT4;
	P7OUT |= BIT3;

	P2DIR |= BIT1;                       // P2.0 and P2.1 output
	P2SEL |= BIT1;                       // P2.0 and P2.1 options select

	TA1CCR0 = timer_period;                            // PWM Period/2
	TA1CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
	TA1CCR2 = 0;                             // CCR2 PWM duty cycle
	TA1CTL = TASSEL_2 + MC_1;                 // ACLK, up mode

	P7SEL |= BIT5;                  // P7.4-7.6 option select
	P7DIR |= BIT5;                  // P7.4-7.6 outputs

	TBCCR0 = timer_period;                           // PWM Period
	TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
	TBCCR3 = 0;                              // CCR3 PWM duty cycle
	TBCTL = TBSSEL_2 + MC_1;                    // SMCLK, upmode

}


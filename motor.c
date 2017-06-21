#include "driverlib.h"
#include "motor.h"

#define timer_period 54

void setPwm(int leftpwmin,int rightpwmin)
{
     //int dutycycle_left,dutycycle_right;

     if (leftpwmin>0)
     {
    	 GPIO_setOutputHighOnPin(
    			 GPIO_PORT_P7,
				 GPIO_PIN1
                	);
    	 GPIO_setOutputLowOnPin(
    			 GPIO_PORT_P7,
				 GPIO_PIN2
                	);
     }
     else{
    	 GPIO_setOutputHighOnPin(
    			 GPIO_PORT_P7,
				 GPIO_PIN2
                	);
    	 GPIO_setOutputLowOnPin(
    			 GPIO_PORT_P7,
				 GPIO_PIN1
                	);
        	}
     if (rightpwmin>0)
     {
    	 GPIO_setOutputHighOnPin(
    			 GPIO_PORT_P4,
				 GPIO_PIN4
    	 );
    	 GPIO_setOutputLowOnPin(
    			 GPIO_PORT_P4,
				 GPIO_PIN0
    	 );
     }
     else{
    	 GPIO_setOutputHighOnPin(
    			 GPIO_PORT_P4,
				 GPIO_PIN0
    	 );
    	 GPIO_setOutputLowOnPin(
    			 GPIO_PORT_P4,
				 GPIO_PIN4
    	 );
     }

     TBCCR3 = abs(leftpwmin)*timer_period/100;
     TA1CCR2 = abs(rightpwmin)*timer_period/100;
}

int abs(int a){
	if (a>=0)
		return a;
	else return (0-a);
}

void motorInit(){
	P2DIR |= BIT1;                       // P2.0 and P2.1 output
	P2SEL |= BIT1;                       // P2.0 and P2.1 options select
	TA1CCR0 = 54;                            // PWM Period/2
	TA1CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
	TA1CCR2 = 0;                             // CCR2 PWM duty cycle
	TA1CTL = TASSEL_2 + MC_1;                 // ACLK, up mode

	P7SEL |= BIT5;                  // P7.4-7.6 option select
	P7DIR |= BIT5;                  // P7.4-7.6 outputs

	TBCCR0 = 54;                           // PWM Period
	TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
	TBCCR3 = 0;                              // CCR3 PWM duty cycle
	TBCTL = TBSSEL_2+MC_1;                    // SMCLK, upmode

	GPIO_setAsOutputPin(
			GPIO_PORT_P7,
			GPIO_PIN2+GPIO_PIN1+GPIO_PIN3
	);
	GPIO_setAsOutputPin(
			GPIO_PORT_P4,
			GPIO_PIN0
	);
	GPIO_setAsOutputPin(
			GPIO_PORT_P4,
			GPIO_PIN4
	);

	GPIO_setOutputHighOnPin(
			GPIO_PORT_P7,
			GPIO_PIN3
	);
}


/**********************************************************************************************************
 *  timers.C
 *
 *  Created on: 28/06/2015
 *      Author: albert
 *
 *  						    ************	*****		***		************
 *     							************	******		***		************
 *      						***				***  *** 	***		***
 *      						***				***	   ***  ***		***
 *      						***				***     *** ***		***
 *      						************	***		 ******		************
 *      						************	***		  *****		************
 *
 **********************************************************************************************************/



/*****************************************************
 * Includes
 *****************************************************/
#include <msp430.h>
#include "timers.h"
#include "stdint.h"


/*****************************************************
 * Variables Declaration
 *****************************************************/
extern short start;
extern uint8_t homing;

timers porttimer;
timer_callBK CB_Timers;

/*****************************************************
 * timers_init function
 *****************************************************/
void timers_init(TXCBack_t TX,TYCBack_t TY,TZCBack_t TZ)
{
	 P2SEL |= BIT3+BIT4+BIT5;                  	// P2.3 - P2.5 option select
	 P2DIR |= BIT3+BIT4+BIT5;                  	// P2.3 - P2.5 outputs

	 //TA2CTL = TASSEL_1 + MC_2 + TACLR + TAIE;  // ACLK, contmode, clear TAR,
	 TA2CTL |= TASSEL_2 + MC_1 + TACLR + TAIE;	// ACLK, contmode, clear TAR,

	 CB_Timers.TX_CB = TX;
	 CB_Timers.TY_CB = TY;
	 CB_Timers.TZ_CB = TZ;

}

/*****************************************************
 * timers_on function
 *****************************************************/
void timer_on (timers timer, unsigned int speed )
{
	TA2CCR0 = speed;
		switch (timer)
		{

			case(timerX):
				 TA2CCTL0|= OUTMOD_4 + CCIE;               	// CCR0 toggle, interrupt enabled

				break;

			case(timerY):
				 TA2CCTL1 |= OUTMOD_4 + CCIE;               	// CCR1 toggle, interrupt enabled
				 TA2CCR1 = speed;
				break;

			case(timerZ):
				 TA2CCTL2 |= OUTMOD_4 + CCIE;               	// CCR2 toggle, interrupt enabled
				 TA2CCR2 = speed;
				break;

		}

}

/*****************************************************
 * timers_off function
 *****************************************************/
void timer_off(timers timer)
{
	switch (timer)
	{
		case(timerX):
		 TA2CCTL0 = OUTMOD_0;               	// CCR0 toggle, interrupt enabled
		 TA2CCTL0 &= ~ CCIE;               	// CCR0 toggle, interrupt enabled
			break;

		case(timerY):
		 TA2CCTL1 = OUTMOD_0;               	// CCR1 toggle, interrupt enabled
		 TA2CCTL1 &= ~ CCIE;               	// CCR1 toggle, interrupt enabled
			break;

		case(timerZ):
		 TA2CCTL2 = OUTMOD_0;               	// CCR2 toggle, interrupt enabled
		 TA2CCTL2 &= ~ CCIE;               	// CCR2 toggle, interrupt enabled
			break;
	}

}


/*****************************************************
 * timer interrupt on port 2
 *****************************************************/
#pragma vector=TIMER2_A0_VECTOR
__interrupt void Timer2_A0 (void)

{
	CB_Timers.TX_CB();
}

/*****************************************************
 * timer interrupt on port 2.2 and 2.4
 *****************************************************/
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)
{
  switch(__even_in_range(TA2IV,14))
  {
    case 0: break;
    case 2:
    		CB_Timers.TY_CB();
    	break;
    case 4:
    		CB_Timers.TZ_CB();
    	break;

    default: break;
 }
}

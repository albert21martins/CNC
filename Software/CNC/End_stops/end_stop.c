/**********************************************************************************************************
 *  end_stop.c
 *
 *  Created on: 27/06/2015
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
#include "end_stop.h"
#include "../ads7843/ads7843.h"
#include "../ssd1289/ssd1289.h"


/*****************************************************
 * Variables
 *****************************************************/
ends end_CB;
touch tch_CB;



/*****************************************************
 * Set_ports function
 * set the input/output pins, interrupts...
 *****************************************************/
void set_ports(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer

	setupDCO();

	P1DIR |= BIT6+BIT3+BIT5+BIT4+BIT0;
	P3DIR |= BIT5+BIT6+BIT7;
	P4DIR |= BIT0+BIT3;
	P6DIR|=BIT0+BIT1+BIT2+BIT4+BIT6;
	P7DIR|=BIT4+BIT0;
	P8DIR|=BIT2;

	//end stops & touch
	P1REN |= BIT2;                            	// Enable P1.4 internal resistance
	P1OUT |= BIT2;                            	// Set P1.4 as pull-Up resistance
	P1IES &= ~BIT2;                             // P1.4 Hi/Lo edge
	P1IFG &= ~BIT2;                           	// P1.4 IFG cleared
	P1IE |= BIT2;                             	// P1.4 interrupt enabled

	P2REN |= BIT2+BIT0+BIT6;                    // Enable P1.4 internal resistance
	P2OUT |= BIT2+BIT0+BIT6;                    // Set P1.4 as pull-Up resistance
	P2IES &= ~BIT2;         	       			// P1.4 Hi/Lo edge
	P2IES &= ~BIT0;         	       			// P1.4 Hi/Lo edge
	P2IES &= ~BIT6;                             // P1.4 Hi/Lo edge
	P2IFG &= ~BIT0;                      		// P1.4 IFG cleared
	P2IFG &= ~BIT2;                      		// P1.4 IFG cleared
	P2IFG &= ~BIT6;                           	// P1.4 IFG cleared
	P2IE |= BIT2+BIT0+BIT6;                     // P1.4 interrupt enabled

	spindle_high();
}


/*****************************************************
 * config_int function
 * set callbacks functions
 *****************************************************/
void config_int(XCBack_t x_CB,YCBack_t y_CB,ZCBack_t z_CB,touchCBack_t t_CB)
{
	end_CB.ES_X = x_CB;
	end_CB.ES_Y = y_CB;
	end_CB.ES_Z = z_CB;
	tch_CB.callBackFunc=t_CB;
}


/*****************************************************
 * Interrupt on pin 1.2
 * X end stop interrupt
 *****************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)

{
	(P1IN&BIT2)?(P1IFG &= ~BIT2):end_CB.ES_X();	//difference between press and release with PIN
}


/*****************************************************
 * Interrupt on pin 2.0, 2.2, 2.6
 * Y,Z interrupt and touch screen interrupt
 *****************************************************/
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)

{
	switch(P2IV)
		{
		case(P2IV_P2IFG0):
				(P2IN&BIT0)?(P2IFG &= ~BIT0):end_CB.ES_Y();	//Y axis callback

			break;
		case(P2IV_P2IFG2):
				(P2IN&BIT2)?(P2IFG &= ~BIT2):end_CB.ES_Z();//Z axis interrupt
			break;
		case(P2IV_P2IFG6):
				tch_CB.callBackFunc();						//touch screen  interrupt
			break;
		}

}



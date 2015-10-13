/**********************************************************************************************************
 *  step_driver.h
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


#ifndef STEP_DRIVER_H_
#define STEP_DRIVER_H_

/*****************************************************
 * Defines
 *****************************************************/
#define __low(var,bit) ((var) &= ~(bit))
#define __high(var,bit) ((var) |= (bit))


//direction pins   3.7, 4.0,4.3
#define dir_X_low() 		__low(P3OUT, BIT7)			//P3.7
#define dir_X_high() 		__high(P3OUT, BIT7)			//P3.7
#define dir_Y_low() 		__low(P4OUT, BIT0)			//P4.0
#define dir_Y_high() 		__high(P4OUT, BIT0)			//P4.0
#define dir_Z_low() 		__low(P4OUT, BIT3)			//P4.3
#define dir_Z_high() 		__high(P4OUT, BIT3)			//P4.3

//enable pins   3.5, 3.6, 7.0
#define en_X_low() 			__low(P3OUT, BIT5)			//P3.5
#define en_X_high() 		__high(P3OUT, BIT5)			//P3.5
#define en_Y_low() 			__low(P3OUT, BIT6)			//P3.6
#define en_Y_high() 		__high(P3OUT, BIT6)			//P3.6
#define en_Z_low() 			__low(P7OUT, BIT0)			//P7.0
#define en_Z_high() 		__high(P7OUT, BIT0)			//P7.0


/*****************************************************
 * Variables declarations
 *****************************************************/
typedef enum
{
	neg,
	pos,
}dir;

typedef struct
{
	 long pulsex;
	 long pulsey;
	 long pulsez;
}pulses;

typedef enum
{
	driverx,
	drivery,
	driverz,
}driver;

typedef struct
{
	driver axes;
	dir enable;
	long step;
	dir direction;
}driver_control;


/*****************************************************
 * Functions Declarations
 *****************************************************/
void init_driver(void);
void move_motor(driver_control move_demand, unsigned int speed);
void actualize_timers(driver stopped);

#endif /* STEP_DRIVER_H_ */

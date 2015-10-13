/**********************************************************************************************************
 *  end_stop.h
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



#ifndef END_STOP_H_
#define END_STOP_H_

/*****************************************************
 * Includes
 *****************************************************/
#include "../ads7843/ads7843.h"

/*****************************************************
 * Variables declaration
 *****************************************************/
typedef void (*XCBack_t) (void);
typedef void (*YCBack_t) (void);
typedef void (*ZCBack_t) (void);

typedef struct
{
	XCBack_t ES_X;
	YCBack_t ES_Y;
	ZCBack_t ES_Z;
}ends;

/*****************************************************
 * Defines
 *****************************************************/
#define __low(var,bit) ((var) &= ~(bit))
#define __high(var,bit) ((var) |= (bit))
//ssd1289 control pins
#define spindle_low() 		__low(P6OUT, BIT4)			//P6.4
#define spindle_high() 		__high(P6OUT, BIT4)			//P6.4

/*****************************************************
 * functions declaration
 *****************************************************/
void set_ports(void);
void config_int(XCBack_t x_CB,YCBack_t y_CB,ZCBack_t z_CB,touchCBack_t t_CB);

/*
 * Port interrupt on ports
 * P1.2
 * P2.0
 * P2.2
 *
 * Spindle motor
 * P6.4
 * */
#endif /* END_STOP_H_ */

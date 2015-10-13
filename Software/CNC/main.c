/**********************************************************************************************************
 * main.c
 *
 *  Created on: 23/06/2015
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
#include <msp430.h>
#include <stdint.h>
#include "ssd1289/ssd1289.h"
#include "ssd1289/screns.h"
#include "ads7843/ads7843.h"
#include "ads7843/position.h"
#include "SD/sd_functions.h"
#include "End_stops/end_stop.h"
#include "End_stops/timers.h"
#include "End_stops/step_driver.h"
#include "SD/drivers/spi.h"
#include "End_stops/gcode.h"
#include "motors/motors_func.h"


/************************************************************************
 * PROFILE CALLBACKS
 ************************************************************************/

static void Touch_CallBack (void);
static void EndStop_X_CallBack (void);
static void EndStop_Y_CallBack (void);
static void EndStop_Z_CallBack (void);


/************************************************************************
 *  Variables
 ************************************************************************/

touch touchscreen;
screens scrnumber;
place lugar;
extern uint8_t homing;
extern short start;
driver_control distance;


/************************************************************************
 *
 * main.c
 *
 ************************************************************************/
void main(void)
{

	set_ports();
	Screen1();
	scrnumber = screen1;
	init();
	spi_initialize();
	config_int(EndStop_X_CallBack, EndStop_Y_CallBack, EndStop_Z_CallBack,Touch_CallBack);
	init_driver();

	__bis_SR_register(GIE);       // Enter LPM4 w/interrupt
}



/**********************************************************************
 *
 * 							CALLBACKS
 *
 **********************************************************************/


/**********************Touch Screen Callback**************************/
static void Touch_CallBack (void)
{
	touchscreen = read();
	scrnumber = position(scrnumber,touchscreen);
	P2IFG &= ~BIT6;
}


/**********************X Axis End Stop Callback**************************/
static void EndStop_X_CallBack (void)
{
	timer_off(timerX);
	distance.direction = pos;
	distance.axes = driverx;
	distance.step = 30000.0;
	distance.enable = pos;
	actualize_timers(driverx);
	lugar.x_pos=0;
	actual_to_previous(lugar);
	en_X_high();
	P1IFG &= ~BIT2;
	move_motor(distance, 1000);
	if (homing)
		home_axis_home(drivery);
}


/**********************Y Axis End Stop Callback**************************/
static void EndStop_Y_CallBack (void)
{
	timer_off(timerY);
	distance.direction = pos;
	distance.axes = drivery;
	distance.step = 30000.0;
	distance.enable = pos;
	actualize_timers(drivery);
	lugar.y_pos=0;
	actual_to_previous(lugar);
	en_Y_high();
	P2IFG &= ~BIT0;               		// P2.0 & P2.2 IFG cleared
	move_motor(distance, 1000);
	if (homing)
		home_axis_home(driverz);
}


/**********************Z Axis End Stop Callback**************************/
static void EndStop_Z_CallBack (void)
{
	timer_off(timerZ);
	distance.direction = neg;
	distance.axes = driverz;
	distance.step = 30000.0;
	distance.enable = pos;
	actualize_timers(driverz);
	lugar.z_pos=0;
	actual_to_previous(lugar);
	en_Z_high();
	homing=0;
	P2IFG &= ~BIT2;               		// P2.0 & P2.2 IFG cleared
	move_motor(distance, 1000);
	if (start)
		read_docs();//read next sd card line
}






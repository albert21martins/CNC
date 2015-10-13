/**********************************************************************************************************
 *  step_driver.C
 *
 *  Created on: 28/06/2015
 *      Author: albert
 *
 *  						    |************|	*****		***		************
 *     							|************|	******		***		************
 *      						|***|			***  *** 	***		***
 *      						|***|			***	   ***  ***		***
 *      						|***|			***     *** ***		***
 *      						|************|	***		 ******		************
 *      						|************|	***		  *****		************
 *
 **********************************************************************************************************/


/*****************************************************
 * Includes
 *****************************************************/
#include <msp430.h>
#include"step_driver.h"
#include"timers.h"
#include"../SD/sd_functions.h"

/*****************************************************
 * Callbacks declaration
 *****************************************************/
static void Driver_X_CallBack (void);
static void Driver_Y_CallBack (void);
static void Driver_Z_CallBack (void);

/*****************************************************
 * Variables declaration
 *****************************************************/
driver_control control;
unsigned long x,y,z;
pulses tics;
extern short start;


/*****************************************************
 * init_driver function
 * set callbacks
 *****************************************************/
void init_driver(void)
{
	 en_X_high();
	 en_Y_high();
	 en_Z_high();
	 timers_init(Driver_X_CallBack,Driver_Y_CallBack,Driver_Z_CallBack);
}

/*****************************************************
 * move_motor function
 *****************************************************/
void move_motor(driver_control move_demand, unsigned int speed)
{
	switch(move_demand.axes)
	{
	case(driverx):
			switch(move_demand.direction)
			{
			case(pos):
					//enable el timer y el counter
					control.step = move_demand.step;
					tics.pulsex = move_demand.step;
					control.enable = pos;
					en_X_low();
					control.direction=move_demand.direction;
					dir_X_high();

					timer_on (timerX, speed);

				break;
			case(neg):
					control.step = move_demand.step;
					tics.pulsex = move_demand.step;
					control.enable = neg;
					en_X_low();
					control.direction=move_demand.direction;
					dir_X_low();

					timer_on (timerX, speed);		//160Hz
				break;
			}
		break;
	case(drivery):
		switch(move_demand.direction)
			{
			case(pos):
					//enable el timer y el counter
					control.step = move_demand.step;
					tics.pulsey = move_demand.step;
					control.enable = pos;
					en_Y_low();
					control.direction=move_demand.direction;
					dir_Y_high();
					timer_on (timerY, speed);		//160Hz
				break;
			case(neg):
					control.step = move_demand.step;
					tics.pulsey = move_demand.step;
					control.enable = neg;
					en_Y_low();
					control.direction=move_demand.direction;
					dir_Y_low();
					timer_on (timerY, speed);		//160Hz
				break;
			}
		break;

	case(driverz):

		switch(move_demand.direction)
			{
			case(pos):
					//enable el timer y el counter
					control.step = move_demand.step;
					tics.pulsez = move_demand.step;
					control.enable = pos;
					en_Z_low();
					control.direction=move_demand.direction;
					dir_Z_high();
					timer_on (timerZ, speed);		//160Hz
				break;
			case(neg):
					control.step = move_demand.step;
					tics.pulsez = move_demand.step;
					control.enable = neg;
					en_Z_low();
					control.direction=move_demand.direction;
					dir_Z_low();
					timer_on (timerZ, speed);		//160Hz
				break;
			}
		break;
	}
}
/*****************************************************
 * actualize_timers function
 * set the timers to 0
 *****************************************************/
void actualize_timers(driver stopped)
{
	switch(stopped)
	{
	case(driverx):
		timer_off(timerX);
		en_X_high();
		tics.pulsex=0;
		x=0;
		control.enable = neg;
		break;
	case(drivery):
		timer_off(timerY);
		en_Y_high();
		tics.pulsey=0;
		y=0;
		control.enable = neg;
		break;
	case(driverz):
		timer_off(timerZ);
		en_Z_high();
		tics.pulsez=0;
		z=0;
		control.enable = neg;
		break;
	}

}


/*****************************************************
 * X Axis Callback
 * count the advanced mm and call read next line if reading SD card file
 *****************************************************/
static void Driver_X_CallBack (void)
{
	x++;
 	if(x>=tics.pulsex)
	{
 		timer_off(timerX);
		en_X_high();
		tics.pulsex=0;
		x=0;
		control.enable = neg;
		if(start && (y==0))		//y eje y ha acabado!!!!!!!!
			read_docs();//read next statement sd card

	}

}

/*****************************************************
 * Y Axis Callback
 * count the advanced mm and call read next line if reading SD card file
 *****************************************************/
static void Driver_Y_CallBack (void)
{
	y++;
	if(y>=tics.pulsey)
	{
		timer_off(timerY);
		en_Y_high();
		tics.pulsey=0;
		y=0;
		control.enable = neg;
		if(start && (x==0))
			read_docs();//read next statement sd card
	}
}
/*****************************************************
 * Z Axis Callback
 * count the advanced mm and call read next line if reading SD card file
 *****************************************************/
static void Driver_Z_CallBack (void)
{
	z++;
	if(z>=tics.pulsez)
	{
		timer_off(timerZ);
		en_Z_high();
		tics.pulsez=0;
		z=0;
		control.enable = neg;
		if(start)
			read_docs();//read next statement sd card
	}
}


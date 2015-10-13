/**********************************************************************************************************
 * motors_func.c
 *
 *  Created on: 02/07/2015
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
 ****************************************************/
#include <msp430.h>
#include <stdint.h>
#include "motors_func.h"
#include "../End_stops/step_driver.h"
#include "../End_stops/gcode.h"
#include "../SD/sd_functions.h"


/*****************************************************
 * Variables
 ****************************************************/

driver_control prove;
place result;
short make;
uint8_t homing=0;


/*****************************************************
 * Home_All function
 * send all the axis to home. One by one
 ****************************************************/
void home_all(void)
{
	//send all home
	 homing=1;
	 home_axis_home(driverx);
}

/*****************************************************
 * Home_axis_home function
 * send a selected axis home
 ****************************************************/
void home_axis_home (driver axis)
{
	//pick the right axis to go home
	if (driverz==axis)
	{
		prove.direction = pos;
	}
	else
	{
		prove.direction = neg;
	}
	 prove.axes = axis;
	 prove.step = -1;		//send PWM for ever until end stop interrupt is triggered
	 move_motor(prove, 1000);
}

/************************************************
 * move_axis function
 * During Jog Control display move the axis certain mm
 ***********************************************/
void move_axis(driver_control motors)
{

	place check_pos,checked;

	switch(motors.axes)
	{
	case(driverx):
				if(motors.direction==pos) check_pos.x_pos = motors.step;		//still mm not steps
				else check_pos.x_pos = -motors.step;
				check_pos.y_pos=0;
				check_pos.z_pos=0;
			break;
	case(drivery):
				if(motors.direction==pos)check_pos.y_pos =motors.step;		//still mm not steps
				else check_pos.y_pos = -motors.step;
				check_pos.x_pos=0;
				check_pos.z_pos=0;
			break;
	case(driverz):
				if(motors.direction==pos)check_pos.z_pos =motors.step;		//still mm not steps
				else check_pos.z_pos = -motors.step;
				check_pos.y_pos=0;
				check_pos.x_pos=0;
			break;
	}
	//sumar

	checked = check_position_advance(check_pos);

	if (checked.x_pos>=0 && checked.y_pos>=0 && checked.z_pos>=0 )
	{
		if((check_pos.x_pos>0) || (check_pos.y_pos>0) || (check_pos.z_pos<0) )
			{motors.direction=pos;}
		else if((check_pos.x_pos<0) || (check_pos.y_pos<0) || (check_pos.z_pos>0))
			{motors.direction=neg;}

		switch(motors.axes)
		{
		case(driverx):motors.step=mm_to_steps(check_pos.x_pos);				// change to steps
				break;
		case(drivery):motors.step=mm_to_steps(check_pos.y_pos);				// change to steps
				break;
		case(driverz):motors.step=mm_to_steps(check_pos.z_pos);				// change to steps
				break;
		}
		move_motor(motors, 1000);
	}
}

/************************************************
 * axis_position function
 * During milling time
 ***********************************************/
place axis_position(place positions)
{
	place pos_prov;

	pos_prov = check_position(positions);		//check if we invalidate the limits
	if(pos_prov.x_pos==0 && pos_prov.y_pos==0 && pos_prov.z_pos==0)
	{
		read_docs();//sd read
	}
	else if(pos_prov.x_pos!=0 || pos_prov.y_pos!=0 || pos_prov.z_pos!=0 )									//if does not
	{
		result=actual_to_previous(positions);	//actualize the positions & return the difference

		if(result.x_pos!=0)						//if x axis has changed
		{
			prove.axes=driverx;
			prove.step=mm_to_steps(result.x_pos);
			if(result.x_pos>0)	prove.direction=pos;
			else prove.direction=neg;
			move_motor(prove, 3000);
			result.x_pos=0;
		}
		if(result.y_pos!=0)
		{
			prove.axes=drivery;
			prove.step=mm_to_steps(result.y_pos);
			if(result.y_pos>0)	prove.direction=pos;
			else prove.direction=neg;
			move_motor(prove, 3000);
			result.y_pos=0;
		}
		if(result.z_pos!=0)
		{
			prove.axes=driverz;
			prove.step=mm_to_steps(result.z_pos);
			if(result.z_pos>0) prove.direction=pos;
			else prove.direction=neg;
			move_motor(prove, 3000);
			result.z_pos=0;
		}

		//aqui iniciar el timer GIE

	}
	return positions;
}

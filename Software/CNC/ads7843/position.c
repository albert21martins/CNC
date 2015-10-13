/******************************************************
 * position.c
 *
 *  Created on: 25/04/2015
 *      Author: albert
 ******************************************************/


/*****************************************************
 * Includes
 *****************************************************/
#include <msp430.h>
#include <stdint.h>
#include "position.h"
#include "ads7843.h"
#include "../End_stops/gcode.h"
#include "../motors/motors_func.h"
#include "../End_stops/step_driver.h"
#include "../End_stops/end_stop.h"
#include "../SD/sd_functions.h"
#include "../SD/pff2a/src/pff.h"
#include "../ssd1289/ssd1289.h"
#include "../ssd1289/screns.h"

/*****************************************************
 * Variables
 *****************************************************/
place movement;
sd_doc listas;
char *point;
short start=0;
driver_control motors;
short spindle_motor=0;


/*****************************************************
 * Position function
 * defines which display is being shown
 *****************************************************/
screens position(screens s, touch tp)
{
	switch(s)
	{
	case(screen1):

		s = Screen_intro( s, tp);
		break;

	case(screen2):

		s = Screen_jog( s, tp);
		break;

	case(screen3):
		s = Screen_sd( s, tp);
		break;
	}
	return s;
}
/*********************************************************************
 * 	Screen 1
 * 	if selected, go to screen 1 or 2 (Jog control or SD card)
**********************************************************************/
screens Screen_intro(screens s, touch tp)
{
	//Jog control
	if((tp.tx>70)&&(tp.tx<120) &&(tp.ty>100) && (tp.ty<156) )
	{
		Screen2();
		s=screen2;
	}
	//SD Card
	if((tp.tx>180)&&(tp.tx<230) &&(tp.ty>100) && (tp.ty<156) )
	{
		listas = Screen3();
		s=screen3;
	}
	return s;
}


/*********************************************************************
 * 	Screen 2
 * 	manual control of the motor axes.
**********************************************************************/
screens Screen_jog(screens s, touch tp)
{
	//Back
	if((tp.tx>20)&&(tp.tx<70) &&(tp.ty>200) && (tp.ty<220) )
	{
		Screen1();
		s=screen1;
	}

/*************************send home commands***********************************/

	//home all
	if((tp.tx>20)&&(tp.tx<80) &&(tp.ty>50) && (tp.ty<80) )
	{
		//send sentence to send home all
		gcode("G90");
	}

	//home x
	else if((tp.tx>20)&&(tp.tx<80) &&(tp.ty>85) && (tp.ty<115) )
	{
		//send sentence to send home x
		home_axis_home(driverx);
	}

	//home y
	else if((tp.tx>20)&&(tp.tx<80) &&(tp.ty>120) && (tp.ty<150) )
	{
		//send sentence to send home y
		home_axis_home(drivery);
	}

	//home z
	else if((tp.tx>20)&&(tp.tx<80) &&(tp.ty>155) && (tp.ty<185) )
	{
		//send sentence to send home z
		home_axis_home(driverz);
	}

/****************************increase/decrease 1 or 10mm X axis***********************************/

	//x--
	else if((tp.tx>130)&&(tp.tx<159) &&(tp.ty>65) && (tp.ty<95) )
	{
		//send sentence to send home all
		//move_x(speed,-10); (si x menor a 0 entonces no!)
		motors.axes=driverx;
		motors.direction=neg;
		motors.step=10.0;
		move_axis(motors);

		//move 10mm backwards
	}

	//x-
	else if((tp.tx>160)&&(tp.tx<190) &&(tp.ty>65) && (tp.ty<95) )
	{
		//send sentence to send home all
		motors.axes=driverx;
		motors.direction=neg;
		motors.step=1.0;
		move_axis(motors);
	}

	//x+
	else if((tp.tx>220)&&(tp.tx<249) &&(tp.ty>65) && (tp.ty<95) )
	{
		//send sentence to send home all
		motors.axes=driverx;
		motors.direction=pos;
		motors.step=1.0;
		move_axis(motors);
	}

	//x++
	else if((tp.tx>250)&&(tp.tx<280) &&(tp.ty>65) && (tp.ty<95) )
	{
		//send sentence to send home all
		motors.axes=driverx;
		motors.direction=pos;
		motors.step=10.0;
		move_axis(motors);
	}

	/****************************increase/decrease 1 or 10mm Z axis***********************************/

	//y--
	else if((tp.tx>130)&&(tp.tx<159) &&(tp.ty>105) && (tp.ty<135) )
	{
		//send sentence to send home all
		motors.axes=drivery;
		motors.direction=neg;
		motors.step=10.0;
		move_axis(motors);
	}

	//y-
	else if((tp.tx>160)&&(tp.tx<190) &&(tp.ty>105) && (tp.ty<135) )
	{
		//send sentence to send home all
		motors.axes=drivery;
		motors.direction=neg;
		motors.step=1.0;
		move_axis(motors);
	}

	//y+
	else if((tp.tx>220)&&(tp.tx<249) &&(tp.ty>105) && (tp.ty<135) )
	{
		//send sentence to send home all
		motors.axes=drivery;
		motors.direction=pos;
		motors.step=1.0;
		move_axis(motors);
	}

	//y++
	else if((tp.tx>250)&&(tp.tx<280) &&(tp.ty>105) && (tp.ty<135) )
	{
		//send sentence to send home all
		motors.axes=drivery;
		motors.direction=pos;
		motors.step=10.0;
		move_axis(motors);
	}

	/****************************increase/decrease 1 or 10mm Y axis***********************************/

	//z-
	else if((tp.tx>130)&&(tp.tx<159) &&(tp.ty>145) && (tp.ty<175) )
	{
		//send sentence to send home all
		motors.axes=driverz;
		motors.direction=neg;
		motors.step=10.0;
		move_axis(motors);
	}

	//z--
	else if((tp.tx>160)&&(tp.tx<190) &&(tp.ty>145) && (tp.ty<175) )
	{
		//send sentence to send home all3s=screen2;
		motors.axes=driverz;
		motors.direction=neg;
		motors.step=1.0;
		move_axis(motors);
	}

	//z+
	else if((tp.tx>220)&&(tp.tx<249) &&(tp.ty>145) && (tp.ty<175) )
	{
		//send sentence to send home all
		motors.axes=driverz;
		motors.direction=pos;
		motors.step=1.0;
		move_axis(motors);
	}

	//z++
	else if((tp.tx>250)&&(tp.tx<280) &&(tp.ty>145) && (tp.ty<175) )
	{
		//send sentence to send home all
		motors.axes=driverz;
		motors.direction=pos;
		motors.step=10.0;
		move_axis(motors);
	}

/*****************************Turn On/Off Spindle motor**********************************/


	//spindle motor
	else if((tp.tx>260)&&(tp.tx<300)&&(tp.ty>200)&&(tp.ty<220))
	{
		if(spindle_motor==0)
		{
			spindle_low(); //spindle on
			spindle_motor=1;
			ssd1289_cs_low();
			ssd1289_fill_rectangle(0xF000, 200, 260, 20, 40);
			ssd1289_string(0x0000,"On",205,270);
			ssd1289_cs_high();
		}

		else
		{
			spindle_high();	//spindle off
			spindle_motor=0;
			ssd1289_cs_low();
			ssd1289_fill_rectangle(0xF00F, 200, 260, 20, 40);
			ssd1289_string(0x0000,"Off",205,265);
			ssd1289_cs_high();
		}


	}

	return s;

}

/*********************************************************************
 * 	Screen 3
 * 	list the files stored on the SD Card
 * 	starts milling file
**********************************************************************/
place mov;

screens Screen_sd(screens s, touch tp)
{
	unsigned int i;
	//Back
	if((tp.tx>20)&&(tp.tx<70) &&(tp.ty>200) && (tp.ty<220) )
	{
		Screen1();
		s=screen1;
	}

/***********************select a file on the sd card************************/
	else if((tp.tx>10)&&(tp.tx<299) &&(tp.ty>50) && (tp.ty<190) )
	{
		for(i=0;i<listas.data_sd;i++)
		{
			 if((tp.tx>60)&&(tp.tx<140) &&(tp.ty>(60+i*20)) && (tp.ty<(80+i*20)) )
			 {
				 point=listas.sd_list+(i*13);

				 ssd1289_cs_low();
				 ssd1289_fill_rectangle(0xffff, 200, 150, 30, 100);
				 ssd1289_string(0x0000,point,200,150);
				 ssd1289_fill_rectangle(0xF000, 200, 260, 20, 40);
				 ssd1289_string(0x0000,"MAKE",205,265);
				 ssd1289_cs_high();

				 start=0;
				 break;
			 }
			 else if((i>=6)&&(tp.tx>180)&&(tp.tx<260) &&(tp.ty>(60+(i-6)*20)) && (tp.ty<(80+(i-6)*20)))
			 {

				 point=listas.sd_list+(i*13);

				 ssd1289_cs_low();
				 ssd1289_fill_rectangle(0xffff, 200, 150, 30, 100);
				 ssd1289_string(0x0000,point,200,150);
				 ssd1289_fill_rectangle(0xF000, 200, 260, 20, 40);
				 ssd1289_string(0x0000,"MAKE",200,265);
				 ssd1289_cs_high();

				 start=0;
				 break;
			 }
		}
		s=screen3;
	}

/***********************select a milling file************************/
	else if((tp.tx>260)&&(tp.tx<300) &&(tp.ty>200) && (tp.ty<220) )
	{
		//open file
		if(start==0)
		{
			open_data(point);
			start=1;
			ssd1289_cs_low();
			ssd1289_fill_rectangle(0xF00F, 200, 260, 20, 40);
			ssd1289_string(0x0000,"Pause",200,265);
			ssd1289_cs_high();
		}
		else
		{
			//to improve!!!
			mov.z_pos=-8;
			actual_to_previous(mov);
			read_docs();
			//pause
//			start=0;
//			ssd1289_cs_low();
//			ssd1289_fill_rectangle(0xF000, 200, 260, 20, 40);
//			ssd1289_string(0x0000,"MAKE",200,265);
//			ssd1289_cs_high();
		}
		s=screen3;
	}
	return s;
}

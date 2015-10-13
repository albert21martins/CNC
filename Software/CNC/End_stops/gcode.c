/**********************************************************************************************************
 *  gcode.c
 *
 *  Created on: 01/07/2015
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
#include "gcode.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../motors/motors_func.h"
#include "../End_stops/step_driver.h"
#include "../End_stops/end_stop.h"
#include "../SD/sd_functions.h"



/*****************************************************
 * Variables Declaration
 ****************************************************/
place anterior;
place actual;
place result;
long steps_to_move;
extern short start;
int val;
uint8_t gruppe;



/*****************************************************
 * gcode function
 ****************************************************/
void gcode(uint8_t *str)
{

	char c_c=*str;
	str++;
	val = get_val(str);
	switch (c_c)
	{
	case'G':
			switch(val)
			{
			case 0: case 1: case 2: case 3: case 80: gruppe = motion; break;
			case 90: case 91: gruppe = gohome; break;
			case 20: case 21: gruppe = units; break;
			case 4: gruppe = pause; break;
			}
			break;

	case'M':
			switch(val)
			{
	 	 	case 0: case 1: case 2: case 30: gruppe = stop; break;
	 	 	case 3: case 4: case 5: gruppe = spindle; break;
	 	 	case 6: gruppe = tool; break;
			}
			break;
	}

	gcode2(str);

}



/*****************************************************
 * gcode2 function
 ****************************************************/
void gcode2(uint8_t *str)
{
	switch (gruppe)
	{
	case motion:
		str+=3;
		switch(*str)
		{
		case 'X':
			str++;
			actual.x_pos = chat_to_int(str);
			if(actual.x_pos>=0)str+=7;
			else str+=8;

		case 'Y':
			str++;
			actual.y_pos = chat_to_int(str);
			if(actual.y_pos>=0) str+=7;
			else str+=8;
			result = axis_position(actual);
			//read_docs();//******************************************************************************************************//
			break;
		case 'Z':
			str++;
			actual.z_pos = chat_to_int(str);
			if(actual.z_pos>=0) str+=7;
			else str+=8;
			//actual.z_pos =actual.z_pos *(-1);
			result = axis_position(actual);
			//read_docs();//******************************************************************************************************//
			break;
		}
		break;
	case gohome:
		home_all();

		break;
	case units:
		read_docs();
		break;
	case pause:
		TA0CTL = TASSEL_1 + MC_2 + TACLR + TAIE;  // ACLK, contmode, clear TAR
		__bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
		//read_docs();
		break;
	case stop:
		start=0;
		break;
	case spindle:
		switch(val)
		{
		case 3: case 4:
			spindle_low(); //spindle on
			read_docs();
			break;
		case 5:
			spindle_high();	//spindle off
			read_docs();
			break;
		}
		break;
	case tool:
		read_docs();//******************************************************************************************************//
		//esperar a la segunda y cuando se llega mostrar en pantalla el ok y esperar a que sea picado
		break;
	}
}



/*****************************************************
 * get_val function
 ****************************************************/
int get_val(uint8_t *dec)
{
	uint8_t number[7];
	uint8_t i=0;
	int num;

	while((*dec != ' '))
	{
		number[i] = *dec;
		dec++;
		i++;
		if((*dec == 0x00)||(*dec == 0x0D))
		{
			break;
		}
	}
	num = (int) atoi(&number);
	return num;
}



/*****************************************************
 * chat_to_int function
 ****************************************************/
float chat_to_int(uint8_t *dec)
{
	uint8_t number[7];
	uint8_t i=0;
	float num;

	if(*dec=='Y')dec++;

	while((*dec != ' '))
	{
		number[i] = *dec;
		dec++;
		i++;
		if(*dec == 0x00)
		{
			break;
		}
	}
	num = (float) atof(&number);
	return num;
}


/*****************************************************
 * actual_to_previous function
 ****************************************************/
place actual_to_previous(place mov)
{

	actual=mov;
	mov.x_pos = mov.x_pos - anterior.x_pos;
	mov.y_pos = mov.y_pos - anterior.y_pos;
	mov.z_pos = mov.z_pos - anterior.z_pos;
	anterior=actual;
	return mov;
}

/*****************************************************
 * actual_to_previous2 function
 ****************************************************/
place actual_to_previous2(place mov)
{
	anterior=actual;
	actual=mov;
	mov.x_pos = mov.x_pos - anterior.x_pos;
	mov.y_pos = mov.y_pos - anterior.y_pos;
	mov.z_pos = mov.z_pos - anterior.z_pos;

	return mov;
}


/*****************************************************
 * check_position_advance function
 ****************************************************/
place check_position_advance(place positione)
{
	place provisional;

	provisional.x_pos = positione.x_pos + actual.x_pos;
	provisional.y_pos = positione.y_pos + actual.y_pos;
	provisional.z_pos = positione.z_pos + actual.z_pos;

	if((provisional.x_pos>=0) && (provisional.y_pos>=0) && (provisional.z_pos>=0))
	{
		positione= actual_to_previous2(provisional);

	}


	return provisional;
	//si se puede entonces, actual to previous

}


/*****************************************************
 * check_position function
 ****************************************************/
place check_position(place positioness)
{
	positioness.x_pos = positioness.x_pos - anterior.x_pos;
	positioness.y_pos = positioness.y_pos - anterior.y_pos;
	positioness.z_pos = positioness.z_pos - anterior.z_pos;

	return positioness;
}


/*****************************************************
 * mm_to_steps function
 ****************************************************/
long mm_to_steps(float mil)
{
	steps_to_move = convert(mil);

	return steps_to_move;
}


/*****************************************************
 * convert function
 ****************************************************/
long convert(float mm)
{	long steps;

	steps = (5142*mm);		//1,4º 1step. 257steps*16= 1turn	1turn:1mm 	//3200

	if(steps<0)
	{
		steps=steps*-1;
	}

	if(steps==0)
	{
		steps=steps;
	}

	return steps;

}


/*****************************************************
 * timer Interrupt
 ****************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
	TA0CTL&= ~TAIE;
	__bic_SR_register_on_exit(LPM3_bits);

}

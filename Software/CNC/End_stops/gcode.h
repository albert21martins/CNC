/**********************************************************************************************************
 *  gcode.h
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


#ifndef GCODE_H_
#define GCODE_H_


/*****************************************************
 * Includes
 ****************************************************/
#include <stdint.h>


/*****************************************************
 * Variables declaration
 ****************************************************/
typedef struct
{
	float x_pos;
	float y_pos;
	float z_pos;
	float f_pos;
}place;

typedef  enum
{
	non_group,
	motion,
	gohome,
	stop,
	units,
	spindle,
	pause,
	tool,
}group;


/*****************************************************
 * Function declaration
 ****************************************************/
float chat_to_int(uint8_t *dec);
place actual_to_previous(place mov);
place actual_to_previous2(place mov);
place check_position(place positioness);
place check_position_advance(place positione);
long mm_to_steps(float mil);
long convert(float mm);
int get_val(uint8_t *dec);
void gcode2(uint8_t *str);
void gcode(uint8_t *str);

#endif /* GCODE_H_ */

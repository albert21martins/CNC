/*
 * position.h
 *
 *  Created on: 25/04/2015
 *      Author: albert
 */

#ifndef POSITION_H_
#define POSITION_H_

/*****************************************************
 * Includes
 *****************************************************/
#include "ads7843.h"
#include <msp430.h>

/*****************************************************
 * variables
 *****************************************************/
typedef enum
{
	screen1,
	screen2,
	screen3
}screens;


/*****************************************************
 * funcion definitions
 *****************************************************/
screens position(screens s, touch tp);
screens Screen_intro(screens s, touch tp);
screens Screen_jog(screens s, touch tp);
screens Screen_sd(screens s, touch tp);

#endif /* POSITION_H_ */

/*
 * ads7843.h
 *
 *  Created on: 13/02/2015
 *      Author: Martins
 */

#ifndef ADS7843_H_
#define ADS7843_H_


/*****************************************************
 * Includes
 *****************************************************/
#include <stdint.h>
#include <msp430.h>

/*****************************************************
 * defines the ports used on the Touch Screen
 *****************************************************/
#define __low(var,bit) ((var) &= ~(bit))
#define __high(var,bit) ((var) |= (bit))


#define clock_low() 	__low(P6OUT, BIT0)		//P6.0
#define clock_high()	__high(P6OUT, BIT0)
#define CS_low() 	__low(P6OUT, BIT1)		 	//P6.1
#define CS_high()	__high(P6OUT, BIT1)
#define DIN_low() 	__low(P6OUT, BIT2)			//P6.2
#define DIN_high()	__high(P6OUT, BIT2)
#define DOUT_low() 	__low(P6OUT, BIT3)			//P6.3
#define DOUT_high()	__high(P6OUT, BIT3)


/*****************************************************
 * variables
 *****************************************************/
typedef void (*touchCBack_t) (void);	//touch callback
typedef struct
{
	uint16_t tx;
	uint16_t ty;
	touchCBack_t callBackFunc;
} touch;
uint16_t X,Y;

/*****************************************************
 * funcion definitions
 *****************************************************/
void init (void);
void write (uint16_t data);
touch read (void);
uint16_t touch_read(void);
int getX(void);
int getY(void);


#endif /* ADS7843_H_ */

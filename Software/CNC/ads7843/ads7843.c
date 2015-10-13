/***********************************************************
 * ads7843.c
 *
 *  Created on: 24/04/2015
 *      Author: albert
 ***********************************************************/


/*****************************************************
 * Includes
 *****************************************************/
#include <msp430.h>
#include "ads7843.h"
#include <stdint.h>

/**********************Variables**********************/
touch touchscr;


/*****************************************************
 * Initializate touch screen pins
 *****************************************************/
void init (void)
{
	clock_high();
	CS_high();
	DIN_high();
	DOUT_high();
}

/*****************************************************
 * write command register into IC via simulated SPI
 *****************************************************/
void write (uint16_t data)
{
	uint16_t i,a;
	clock_low();
	for (i=0; i<8;i++)
	{
		a = data<<i;
		a & 0x80? DIN_high() : DIN_low();

		clock_low(); __delay_cycles(1);
		clock_high();
	}
}

/*****************************************************
 * buffers the data received
 *****************************************************/
uint16_t touch_read(void)
{
	uint16_t data=0,i;
	for(i=0;i<12;i++)
	{
		data<<=1;
		clock_high(); __delay_cycles(1);
		clock_low();
		if(P6IN & BIT3)
		{
			data++;
		}
	}
	return (data);
}

/*****************************************************
 * read parameters from the touch controller
 *****************************************************/
touch read (void)
{
	uint16_t x=0,y=0,i;

	CS_low();

	for(i=0; i<10;i++)
	{
		write(0x90);	//send command to receive Y position
		clock_low(); __delay_cycles(1);
		clock_high();
		y+= touch_read();

		write(0xD0);    //send command to receive X position
		clock_low(); __delay_cycles(1);
		clock_high();
		x+=touch_read();
	}
	CS_low();
	X=x/10;
	Y=y/10;
	touchscr.tx = getX();
	touchscr.ty = getY();
	return(touchscr);
}

/*****************************************************
 * Set the X received parameter to real ones.
 *****************************************************/
int getX(void)
{
	int value;
	value = (Y-300)/11;
	if (value<0) value=0;
	return (value);
}
/*****************************************************
 * Set the Y received parameter to real ones.
 *****************************************************/
int getY(void)
{
	int value;

	value = ((X-180)/15);
	if (value<0) value=0;
	return (value);

}


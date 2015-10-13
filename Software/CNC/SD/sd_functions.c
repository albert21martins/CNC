/**********************************************************************************************************
 * sd_functions.c
 *
 *  Created on: 26/06/2015
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
 *****************************************************/
#include <msp430.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "sd_functions.h"
#include "pff2a/src/diskio.h"
#include "pff2a/src/pff.h"
#include "drivers/spi.h"
#include "../End_stops/gcode.h"

/*****************************************************
 * Variables
 *****************************************************/
char list[10][13];
char Buff[27]; // serial and general buffer
char Line[27];
unsigned short s1;
unsigned int f=0;
unsigned long punter=0;

DSTATUS resu;
FATFS fs;			/* File system object */
DIRE dir;			/* Directory object */
FILINFO fno;		/* File information */
WORD s1;



/*****************************************************
 * GetNames functions
 * gethe names of every file on the SD card
 *****************************************************/

char* getnames(void)
{
	//char *ptr= NULL;

		int i=0;
		int a = 5;
		char *ptr = NULL;
		ptr = &a;

		resu = disk_initialize();		// disk initialize
		resu = disk_initialize();		// disk initialize
		resu = disk_initialize();		// disk initialize

	    pf_mount(&fs);					//fats init


	    while (*ptr == ' ')
	    ptr++;
	    resu = pf_opendir(&dir, ptr);
	    s1 = 0;

	       for (;;)
	       {
			   resu = pf_readdir(&dir, &fno);
			   if (resu != FR_OK)
				   break;
			   if (!fno.fname[0])
				  break;

				   strncpy(list[i],fno.fname,13);
				   i++;
				   __delay_cycles(5);

				   s1++;
	       }

	       return list;
}


/*****************************************************
 * GetNames functions
 * Open a file on the SD card
 *****************************************************/

void open_data(char *ptr)
{
	pf_open(ptr);
	read_docs();
}



/*****************************************************
 * Read_Docs function
 * Read the content of a file
 * Send the lines to gcode interpreter
 *****************************************************/
void read_docs(void)
{

		P8OUT &= ~BIT1;


		if(pf_read(Buff, sizeof(Buff), &s1)==0)
		{
			while(Buff[f]!='\n')
			{

				Line[f]= Buff[f];
					f++;
			}
			punter=punter+f+1;
			pf_lseek(punter);
			f=0;
			gcode(Line);
			P8OUT |= BIT1;
			if(strncmp(Line,"M02",3)==0)
			{
				P8OUT |= BIT1;
				punter=0;
			}
		}
		else
		{
			P8OUT |= BIT1;
		}
}


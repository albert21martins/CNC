/**********************************************************************************************************
 * screens.c
 *
 *  Created on: 24/06/2015
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
#include "ssd1289.h"
#include "logos.h"
#include "screns.h"
#include "../SD/sd_functions.h"


/************************************************************************
 *  Variables
 ************************************************************************/

sd_doc docs;
uint8_t i,j;
uint8_t k=60, l=30;
char names[13];
char *lista;


/************************************************************************
 *  First Screen
 *  shows menus: Jog control and SD card files
 ************************************************************************/

void Screen1(void)
{
	ssd1289_rest_high();
	ssd1289_cs_low();
	init_TFT();
	ssd1289_fill(0xFFFF);
	ssd1289_rectangle(0x0000,0,0,239,319);
	ssd1289_string(0x0000,"Author: Albert",200,100);
	drawbitmap(85, 10, 235, 69, info);
	drawbitmap(70, 100, 120, 156, Captura);
	ssd1289_string(0x0000,"Jog",125,83);
	drawbitmap(180, 100, 230, 156, Captura);
	ssd1289_string(0x0000,"SD",125,198);
	ssd1289_cs_high();
	ssd1289_rest_high();__delay_cycles(50);
	ssd1289_rest_low();	__delay_cycles(50);
	ssd1289_rest_high();__delay_cycles(50);
}


/************************************************************************
 *  Second Screen
 *  shows Jog Control: display motor controls
 ************************************************************************/
void Screen2(void)
{
	ssd1289_cs_low();
	ssd1289_fill(0xFFFF);
	ssd1289_string(0x0000,"JOG CONTROL",20,120);
	//separation lines
	ssd1289_hline(0x0000, 42, 10, 299);
	ssd1289_hline(0x0000, 195, 10, 299);
	ssd1289_vline(0x0000, 50, 90, 140);
	//back button
	drawbitmap(20, 200, 70, 220, back);
	//home
	drawbitmap(20, 50, 50, 81, home);
	ssd1289_string(0x0000,"ALL",65,55);
	drawbitmap(20, 85, 50, 116, home);
	ssd1289_string(0x0000,"X",100,55);
	drawbitmap(20, 120, 50, 151, home);
	ssd1289_string(0x0000,"Y",135,55);
	drawbitmap(20, 155, 50, 186, home);
	ssd1289_string(0x0000,"Z",170,55);

	/**************************************
	 * Steps
	 *************************************/
	//X
	ssd1289_string(0x0000,"-",75,115);
	ssd1289_fill_rectangle(0x8410,65, 130, 30, 30);
	ssd1289_fill_rectangle(0xC618,65, 160, 30, 30);
	ssd1289_rectangle(0x0000,65, 190, 30, 30);
	ssd1289_string(0x0000,"X",75,200);
	ssd1289_fill_rectangle(0xC618,65, 221, 30, 30);
	ssd1289_fill_rectangle(0x8410,65, 251, 30, 30);
	ssd1289_string(0x0000,"+",75,290);
	//Y
	ssd1289_string(0x0000,"-",115,115);
	ssd1289_fill_rectangle(0x8410,105, 130, 30, 30);
	ssd1289_fill_rectangle(0xC618,105, 160, 30, 30);
	ssd1289_rectangle(0x0000,105, 190, 30, 30);
	ssd1289_string(0x0000,"Y",115,200);
	ssd1289_fill_rectangle(0xC618,105, 221, 30, 30);
	ssd1289_fill_rectangle(0x8410,105, 251, 30, 30);
	ssd1289_string(0x0000,"+",115,290);
	//Z
	ssd1289_string(0x0000,"-",155,115);
	ssd1289_fill_rectangle(0x8410,145, 130, 30, 30);
	ssd1289_fill_rectangle(0xC618,145, 160, 30, 30);
	ssd1289_rectangle(0x0000,145, 190, 30, 30);
	ssd1289_string(0x0000,"Z",155,200);
	ssd1289_fill_rectangle(0xC618,145, 221, 30, 30);
	ssd1289_fill_rectangle(0x8410,145, 251, 30, 30);
	ssd1289_string(0x0000,"+",155,290);
	//spindle motor
	ssd1289_string(0x0000,"Spindle Motor",200,150);
	ssd1289_fill_rectangle(0xF000, 200, 260, 20, 40);
	ssd1289_string(0x0000,"Off",200,270);
	ssd1289_cs_high();

}


/************************************************************************
 *  Third Screen
 *  shows SD Card Files: display every file stored on the sd card
 ************************************************************************/
sd_doc Screen3(void)
{
	*names=0;
	lista = 0;
	ssd1289_cs_low();
	ssd1289_fill(0xFFFF);
	ssd1289_string(0x0000,"SD Card ",20,130);
	ssd1289_hline(0x0000, 42, 10, 299);
	drawbitmap(20, 200, 70, 220, back);
	ssd1289_rectangle(0x0000, 50, 10, 140, 299);
	lista = getnames();
	for(i=0; i<10; i++)
	{
		if(*lista!=0)
		{
			for(j=0;j<13;j++)
			{
				names[j]=*lista++;
			}
			ssd1289_string(0x0000,names,k,l);
			k+=20;
			if(i==5)
			{
				k=60;
				l=180;
			}
		}
		else
		{
			k=60;
			l=20;
			break;
		}
	}
	ssd1289_cs_high();
	lista=lista-(i*13);
	docs.data_sd=i;
	docs.sd_list = lista;
	return docs;
}

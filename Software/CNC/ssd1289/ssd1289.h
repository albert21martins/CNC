/**********************************************************************************************************
 * ssd1289.h
 *
 *  Created on: 23/06/2015
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

#ifndef SSD1289_H_
#define SSD1289_H_

/*****************************************************
 * Includes
 ****************************************************/

#include <msp430.h>
#include <stdint.h>


/*****************************************************
 * Defines
 ****************************************************/

//global
#define __low(var,bit) ((var) &= ~(bit))
#define __high(var,bit) ((var) |= (bit))

//ssd1289 control pins
#define ssd1289_cs_low() 	__low(P8OUT, 0x04)			//P8.2
#define ssd1289_cs_high() 	__high(P8OUT, 0x04)			//P8.2
#define ssd1289_rs_low() 	__low(P1OUT, 0x40)			//P1.6
#define ssd1289_rs_high() 	__high(P1OUT, 0x40)			//P1.6
#define ssd1289_wr_low() 	__low(P6OUT, 0x40)			//P6.6
#define ssd1289_wr_high()	__high(P6OUT, 0x40)			//P6.6
#define ssd1289_rest_low() 	__low(P7OUT, 0x10)			//P7.4
#define ssd1289_rest_high()	__high(P7OUT, 0x10)			//P7.4

// 74hc595 control pins
#define stcp_low() 	__low(P1OUT, BIT4)					//P1.4
#define stcp_high() __high(P1OUT, BIT4)					//P1.4
#define shcp_low() 	__low(P1OUT, BIT5)					//P1.5
#define shcp_high() __high(P1OUT, BIT5)					//P1.5
#define data_low() 	__low(P1OUT, BIT3)					//P1.3
#define data_high() __high(P1OUT, BIT3)					//P1.3

//screen size
#define SSD1289_WIDTH 320
#define SSD1289_HEIGHT 240

/*****************************************************
 * Functions
 ****************************************************/
void init_TFT(void);
void ssd1289_send(uint16_t cmd, uint16_t data);
void ssd1289_write(uint16_t raw);
void ssd1289_fill(uint16_t color);
void ssd1289_send_cmd(uint16_t raw);
void ssd1289_send_data(uint16_t raw);
void ssd1289_set_cursor(uint16_t y, uint16_t x);
void ssd1289_pixel(uint16_t color, uint16_t y, uint16_t x);
void ssd1289_vline(uint16_t color, uint16_t y, uint16_t x, uint16_t height);
void ssd1289_hline(uint16_t color, uint16_t y, uint16_t x, uint16_t width);
void ssd1289_rectangle(uint16_t color, uint16_t y, uint16_t x, uint16_t height, uint16_t width);
void ssd1289_char(uint16_t color, char ch, uint16_t y, uint16_t x);
void ssd1289_string(uint16_t color, char *string, uint16_t y, uint16_t x);
void drawbitmap(uint16_t x, uint16_t y, uint16_t sx, uint16_t sy, uint16_t *data);
void SetVcoreUp (unsigned int level);
void setupDCO(void);
void ssd1289_vdiagonal(uint16_t color, uint16_t y, uint16_t x, uint16_t sy, uint16_t sx);
void ssd1289_fill_rectangle(uint16_t color, uint16_t y, uint16_t x, uint16_t height, uint16_t width);

#endif /* SSD1289_H_ */

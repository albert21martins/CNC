/**********************************************************************************************************
 *  timers.h
 *
 *  Created on: 28/06/2015
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



#ifndef TIMERS_H_
#define TIMERS_H_

/*****************************************************
 * Callbacks declaration
 *****************************************************/
typedef void (*TXCBack_t) (void);
typedef void (*TYCBack_t) (void);
typedef void (*TZCBack_t) (void);

/*****************************************************
 * Variables Declaration
 *****************************************************/
typedef enum
{
	timerX,
	timerY,
	timerZ,
}timers;

typedef struct
{
	TXCBack_t TX_CB;
	TYCBack_t TY_CB;
	TZCBack_t TZ_CB;

}timer_callBK;

/*****************************************************
 * Functions Declaration
 *****************************************************/
void timers_init(TXCBack_t TX,TYCBack_t TY,TZCBack_t TZ);
void timer_on(timers timer,unsigned int speed);
void timer_off(timers timer);

#endif /* TIMERS_H_ */

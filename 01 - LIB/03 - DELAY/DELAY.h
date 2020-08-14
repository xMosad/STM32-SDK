/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/8/2020                          */
/*****************************************************/
#ifndef DELAY_H
#define DELAY_H 



#ifndef SYSTEMCORECLOCK 
	#define SYSTEMCORECLOCK 8000000
#endif

// 6000 for keil and 12000 for eclipce
// must define the system clock first if not the default is 8 MHZ
void delay_ms(u32 ms) ;


#endif 
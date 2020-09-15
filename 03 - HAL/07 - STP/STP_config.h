/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
#ifndef STP_CONFIG_H
#define STP_CONFIG_H

/*
	Options  :

 */
#define     STP_PINS_OUTPUT_MODE     GPIO_OUTPUT_2MHZ_PP

/* Configuration pins */

#define STP_SERIAL_DATA   PORTA,PIN0
#define STP_SHIFT_CLK     PORTA,PIN1
#define STP_STORE_CLK     PORTA,PIN2

/* MSB of the parellel data
       if using one it will be 7
	   if using two it will be 15 ....etc
	   */
#define      STP_MSP     15



#endif

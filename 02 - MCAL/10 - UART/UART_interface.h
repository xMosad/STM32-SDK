/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 20/9/2020                          */
/*****************************************************/

/***********************************************************
	* Pre conitions : 
		1 - Enable RCC for the used UART module 
		2 - Configure RX and TX pins as GPIO pins
			RX -> input floating 
			TX -> Alternative output
		3 - populate configuration table in config.c 
************************************************************/
		
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/******************* Public data types *******************/

/**** Timer channels ****/
typedef enum {
	UART1,
	UART2,
	UART3,
	MAX_TIMERS
}UART_Ch_t;

/********************* Prototypes **********************/

/* 
  * UART_voidInit - > Intialize UART module  
*/
void UART_voidInit(void);

/* 
  * UART_voidSendDataSynch - > send a character or string to uart  
  * I/P : UART_Ch_t   /  pointer to (u8)
*/
void UART_voidSendDataSynch(UART_Ch_t copy_ch , u8 *copy_u8data);

/* 
  * UART_voidRecDataSynch - > receive a character or string to uart  
  * I/P : UART_Ch_t   /  pointer to (u8)  /   (u8) length of data 
*/
void UART_voidRecDataSynch (UART_Ch_t copy_ch , u8 *copy_u8data , u8 copy_u8DataLength)


#endif

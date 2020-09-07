/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 7/9/2020                          */
/*****************************************************/


#include "STD_TYPES.h"

#include "LEDMRX_config.h"

/* Port id */
#define    PORTA      0
#define    PORTB      1
#define    PORTC      2
#define    PORTD      3

/*  pins number */
#define    PIN0       0
#define    PIN1       1
#define    PIN2       2
#define    PIN3       3
#define    PIN4       4
#define    PIN5       5
#define    PIN6       6
#define    PIN7       7
#define    PIN8       8
#define    PIN9       9
#define    PIN10      10
#define    PIN11      11
#define    PIN12      12
#define    PIN13      13
#define    PIN14      14
#define    PIN15      15

/* Enter each pin in the rows as PORTx and PINx */
u8 LEDMRX_globalRows[(LEDMRX_ROWS_NUMBER * 2 )] = {
	PORTA,PIN0,
    PORTA,PIN1,
    PORTA,PIN2,
    PORTA,PIN3,
    PORTA,PIN4,                                
    PORTA,PIN5,
    PORTA,PIN6,
    PORTA,PIN7
};

/* Enter each pin in the colomns as PORTx and PINx */
u8 LEDMRX_globalColoumns[(LEDMRX_COLOUMNS_NUMBER *2)] = {
	PORTB,PIN0,
    PORTB,PIN1,
    PORTB,PIN5,
    PORTB,PIN6,
    PORTB,PIN7, 
    PORTB,PIN8,
    PORTB,PIN9,
    PORTB,PIN10
};


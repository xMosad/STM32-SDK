/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 31/8/2020                          */
/*****************************************************/
#ifndef LEDMRX_PRIVATE_H
#define LEDMRX_PRIVATE_H


/*  contants  */
#define LEDMRX_DELAY (1000000 / (LEDMRX_Frame_RATE * LEDMRX_ROWS_NUMBER) )

/* Configuration pin mapping */
extern u8 LEDMRX_globalRows[(LEDMRX_ROWS_NUMBER * 2 )];
extern u8 LEDMRX_globalColoumns[(LEDMRX_COLOUMNS_NUMBER*2)];

/* private functions prototypes*/
static void SetRowValues (u8 copy_u8Value);




#endif
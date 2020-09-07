/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 7/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"

/* module includes */
#include "LEDMRX_interface.h"
#include "LEDMRX_config.h"
#include "LEDMRX_private.h"

/*************** Global variables *****************/
static volatile u8 global_u8CurrentColoumn = 2 ;
static volatile u8 global_u8PreviosColoumn = 0 ;
static volatile u8 *global_u8Data ;
static volatile u8 *global_u8StartData ;
static volatile u8 *global_u8StringEnd ;

/**************** Intialization ******************/
void LEDMRX_voidInit(void)
{
	/* Making the i/o pins for row output */
	for (u8 i = 0 ; i < (LEDMRX_ROWS_NUMBER*2) ; i += 2){
		GPIO_voidSetPinMode(LEDMRX_globalRows[i] , LEDMRX_globalRows[i+1], LEDMRX_OUTPUT_MODE);
	}
	
	/* Making the i/o pins for coloumns output */
	for (u8 i = 0 ; i < (LEDMRX_COLOUMNS_NUMBER*2) ; i += 2){
		GPIO_voidSetPinMode(LEDMRX_globalColoumns[i] , LEDMRX_globalColoumns[i+1], LEDMRX_OUTPUT_MODE);
		GPIO_voidsetPinValue(LEDMRX_globalColoumns[i] , LEDMRX_globalColoumns[i+1], !(LEDMRX_COLOUMN_VOLTAGE));
	}
}

/********************* Tasks *********************/
void LEDMRX_voidDisplay (void)
{
	/* Activate the current column to write to  a specific row */
	GPIO_voidsetPinValue(LEDMRX_globalColoumns[global_u8CurrentColoumn] , LEDMRX_globalColoumns[global_u8CurrentColoumn+1], LEDMRX_COLOUMN_VOLTAGE);
	/* Diactivate a previous column so data will not be written to it */
	GPIO_voidsetPinValue(LEDMRX_globalColoumns[global_u8PreviosColoumn] , LEDMRX_globalColoumns[global_u8PreviosColoumn+1], !(LEDMRX_COLOUMN_VOLTAGE));
	/* Write to the rows */
	SetRowValues(global_u8Data[(global_u8CurrentColoumn/2)]);
	/* Shift to another column */
	global_u8CurrentColoumn += 2 ;
	global_u8PreviosColoumn += 2 ;
	/* Index reached the last colomn so will begin from zero again */
	if ( global_u8CurrentColoumn == (LEDMRX_COLOUMNS_NUMBER *2) ){
		global_u8CurrentColoumn = 0;
	}
	else if (global_u8PreviosColoumn == (LEDMRX_COLOUMNS_NUMBER *2)){
		global_u8PreviosColoumn=0;
	}
}

void LEDMRX_voidDisplayShiftText (void)
{
	/* While the pointer to data less than the end of string will inceremnt data pointer*/
	if ((global_u8Data) < global_u8StringEnd)	{
		global_u8Data++;
	}
	else{
		global_u8Data = global_u8StartData;
	}
}

/****************** Setter functions ***********************/
void LEDMRX_voidSetData (u8 *copy_u8Data){
	global_u8Data = copy_u8Data ;
	global_u8StartData=global_u8Data;
}

void LEDMRX_voidSetStringLenght(u8 copy_u8Data){
	global_u8StringEnd = global_u8StartData+copy_u8Data ;
}


/***********  Private functions  *************/
static void SetRowValues (u8 copy_u8Value)
{
	u8 local_u8Bit = 0 ;
	for (u8 i = 0 ; i < (LEDMRX_COLOUMNS_NUMBER*2) ; i += 2){
		local_u8Bit  = GIT_BIT(copy_u8Value , (i / 2) ) ;
		GPIO_voidsetPinValue(LEDMRX_globalRows[i] , LEDMRX_globalRows[i+1] , local_u8Bit );
	}

}                                         

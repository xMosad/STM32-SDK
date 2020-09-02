/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 31/8/2020                          */
/*****************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "STK_interface.h"

/* module includes */
#include "LEDMRX_interface.h"
#include "LEDMRX_config.h"
#include "LEDMRX_private.h"



void LEDMRX_voidInit(void)
{
	/* Initialize the systick */
	STK_voidInit();
	
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


void LEDMRX_voidDisplay (u8 *copy_u8Data)
{
	for (u8 i = 0 ;i < (LEDMRX_COLOUMNS_NUMBER*2) ; i += 2){
		/* Activate a coloumn */
		GPIO_voidsetPinValue(LEDMRX_globalColoumns[i] , LEDMRX_globalColoumns[i+1], LEDMRX_COLOUMN_VOLTAGE);
		/* Write to the rows */
		SetRowValues(copy_u8Data[(i/2)]);
		/* Delay */
		STK_voidSetBusyWait(LEDMRX_DELAY , TIME_US);
		/* Diactivate a coloumn */
		GPIO_voidsetPinValue(LEDMRX_globalColoumns[i] , LEDMRX_globalColoumns[i+1], !(LEDMRX_COLOUMN_VOLTAGE));
	}										  
}

void LEDMRX_voidDisplayShiftText (u8 *copy_u8Data , u16 copy_u8Time , u8 copy_u8TextSize)
{
	/* calculate how much to loop in while */
	copy_u8Time = copy_u8Time / (LEDMRX_COLOUMNS_NUMBER * (LEDMRX_DELAY /1000 ));
	/* Hold the time to update it after every shift */
	u16 Local_u16Hold =copy_u8Time  ;
	
	/* Looping through the text */
	while(copy_u8TextSize--){
		/* making delay betweem shifts */
		while (copy_u8Time--){
			LEDMRX_voidDisplay(copy_u8Data);
		}
		copy_u8Data++;
		copy_u8Time = Local_u16Hold;
	}
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

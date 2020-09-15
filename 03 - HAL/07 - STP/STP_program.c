/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "STK_interface.h"

/* module includes */
#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"

void STP_voidInit(void)
{
	GPIO_voidSetPinMode(STP_SERIAL_DATA , GPIO_OUTPUT_2MHZ_PP);
	GPIO_voidSetPinMode(STP_SHIFT_CLK   , GPIO_OUTPUT_2MHZ_PP);
	GPIO_voidSetPinMode(STP_STORE_CLK   , GPIO_OUTPUT_2MHZ_PP);
}

void STP_voidSendSynch(u16 copy_u16DataToSend)
{
	s8 local_u8Counter ;
	u8 local_u8Bit ;
	for (local_u8Counter = STP_MSP ; local_u8Counter >= 0 ; local_u8Counter--){
		/* Send to serial pin */
		local_u8Bit = GIT_BIT(copy_u16DataToSend ,local_u8Counter);
		GPIO_voidsetPinValue (STP_SERIAL_DATA ,local_u8Bit);
		
		/* Send pulse to shift clk */
		GPIO_voidsetPinValue (STP_SHIFT_CLK ,HIGH);
		STK_voidSetBusyWait(2 , TIME_US);
		GPIO_voidsetPinValue (STP_SHIFT_CLK ,LOW);
		STK_voidSetBusyWait(2 , TIME_US);
	}
	
	/* Send pulse to store */
	GPIO_voidsetPinValue (STP_STORE_CLK ,HIGH);
	STK_voidSetBusyWait(2 , TIME_US);
	GPIO_voidsetPinValue (STP_STORE_CLK ,LOW);
	STK_voidSetBusyWait(2 , TIME_US);
}



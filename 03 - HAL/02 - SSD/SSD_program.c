/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/8/2020                          */
/*****************************************************/

/* Library includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DELAY.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "RCC_interface.h"

/* Specific module includes  */
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

/* Initialize some parameters for the multiplexing mode*/
#if SSD_MULTIPLEXING_NUMBER > 1
	#if   SSD_TYPE == COMMON_CATHOD 
		#define SSD_SELCET_INIT_STATE HIGH 
		#define SSD_SELCET_STATE      LOW
	
	#elif SSD_TYPE == COMMON_ANODE	
		#define SSD_SELCET_INIT_STATE LOW 
		#define SSD_SELCET_STATE      HIGH
	#endif
	const u8 SSD_selectPins[4]    = {SSD_RIGHT_SELECT , SSD_MID1_SELECT , SSD_MID2_SELECT , SSD_LEFT_SELECT };
#endif
	
	

/* public variables */
const u8 SSD_values[10]		= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


void SSD_voidInit(SSD_selectID_t copy_id){
	// Enable the port clock
	RCC_voidEnableClock(RCC_APB2 , (copy_id.SSD_portId + IOPA_PERIPHERAL) );
	// Making the pins output
	for (u8 i = copy_id.SSD_startPin ; i <= (copy_id.SSD_startPin+7) ; i++ ){
		GPIO_voidSetPinMode(copy_id.SSD_portId , i , SSD_OUTPUT_MODE );
	}
	// To initialize the selection pins
	#if SSD_MULTIPLEXING_NUMBER > 1 
		// Enable the port clock
		RCC_voidEnableClock(RCC_APB2 , (SSD_SELECT_PORT + IOPA_PERIPHERAL) );
		// configure the select pins as output and setting them to the initialize state
		for (u8 i = 0 ; i < SSD_MULTIPLEXING_NUMBER ; i++){
			GPIO_voidSetPinMode (SSD_SELECT_PORT , SSD_selectPins[i] , SSD_OUTPUT_MODE       );
			GPIO_voidsetPinValue(SSD_SELECT_PORT , SSD_selectPins[i] , SSD_SELCET_INIT_STATE );
		}
	#endif
}

void SSD_voidWriteNumber (SSD_selectID_t copy_id , u8 copy_u8Number){
	/* select the ssd type */
	#if   SSD_TYPE == COMMON_CATHOD 	
		GPIO_voidWritePins (copy_id.SSD_portId , copy_id.SSD_startPin , PINS_7 , SSD_values[copy_u8Number] );
	
	#elif SSD_TYPE == COMMON_ANODE			
		GPIO_voidWritePins (copy_id.SSD_portId , copy_id.SSD_startPin , PINS_7 , ~ SSD_values[copy_u8Number]  ); 
		
	#endif
}

#if SSD_MULTIPLEXING_NUMBER > 1
	void SSD_voidUpdateMultiplexing (SSD_selectID_t copy_id , u16 copy_u16Number){
		u8 number[SSD_MULTIPLEXING_NUMBER]; // store the number devided to ones
		u8 i = 0 ;
		if (copy_u16Number == 0 ) {
			for(u8 i = 0 ; i < SSD_MULTIPLEXING_NUMBER ; i ++){
				number[i] = 0 ;
			}
		}
		/* Devide number to onse */
		while (copy_u16Number){
			number[i] = copy_u16Number % 10 ;
			copy_u16Number = copy_u16Number / 10             ;
			i++;
		}
		for(u8 i = 0 ; i < SSD_MULTIPLEXING_NUMBER ; i ++){
			// Select the right SSD and write to it 
			GPIO_voidsetPinValue(SSD_SELECT_PORT , SSD_selectPins[i] , SSD_SELCET_STATE      );
			SSD_voidWriteNumber(copy_id , number[i]);
			delay_ms(SSD_DELAY);
			GPIO_voidsetPinValue(SSD_SELECT_PORT , SSD_selectPins[i] , SSD_SELCET_INIT_STATE );
		}
		
	}
#endif





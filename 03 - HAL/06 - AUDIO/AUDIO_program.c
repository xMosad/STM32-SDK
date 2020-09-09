/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"

/* module includes */
#include "AUDIO_interface.h"
#include "AUDIO_config.h"
#include "AUDIO_private.h"

/* Data */
#include "song.h"
/****** Global variables  *******/
 u8 global_u8PinsMap[16] = {AUDIO_DAC0 , AUDIO_DAC1 , AUDIO_DAC2 , AUDIO_DAC3 ,                                             
							AUDIO_DAC4 , AUDIO_DAC5 ,  AUDIO_DAC6 , AUDIO_DAC7 };
u16 global_u16Index ; 																			
                                       
/********* Initialization ********/
void AUDIO_voidInit (void)
{
	for (u8 i = 0 ; i < 16 ; i += 2)
	{
		GPIO_voidSetPinMode(global_u8PinsMap[i] , global_u8PinsMap[i+1] , AUDIO_DAC_OUTPUT_MODE);
	}
}                           
   
/*********** Tasks ************/ 
void AUDIO_voidSetDAC (void){
	GPIO_voidWritePins(AUDIO_DAC0 , PINS_8 , AUDIO_song[global_u16Index]);
	global_u16Index++;
	if (global_u16Index == AUDIO_SONG_LENGHT){
		global_u16Index = 0 ;
	}
}
  
